#include "login_socket.h"
#include "server.h"
#include "storage.h"
#include "debug_update.h"
#include "urlencode.h"
#include "json.h"
#include "json_value.h"

void LoginSocket::updateDb()
{
    Field *field;

    shared_ptr<QueryResult> qres_social ( iDBManager->getSSDatabase()->queryNA ( DB_SELECT_SOCIAL_NET_SQL) );
    if ( !qres_social.get() )
    {
        traceerr("%s", "Error fetching social network configuration data from DB!");
        exit(1);
    }
    do
    {
        field = qres_social->fetch();
        int soc_net_id = field[0].getUInt32();
        _social_net[soc_net_id].app_id 		= field[1].getString();
        _social_net[soc_net_id].app_secret 	= field[2].getString();
        _social_net[soc_net_id].login_path 	= field[3].getString();
        _social_net[soc_net_id].iframe 		= field[4].getString();
    }
    while ( qres_social->nextRow() );
}
LoginSocket::LoginSocket(const char* listen_address, uint32 port) : ListenSocket(listen_address, port)
{
    updateDb();
    _social_net[SocialNetDesc::VK].handler = &LoginSocket::vkReq;
    _social_net[SocialNetDesc::OK].handler = &LoginSocket::okReq;
    _social_net[SocialNetDesc::MM].handler = &LoginSocket::mmReq;
    _social_net[SocialNetDesc::FB].handler = &LoginSocket::fbReq;

    uint32 num_threads = iServer->getNumWorkerThreads();
    for (uint32 i = 0; i < num_threads; ++i)
    {
        iThreadCore->startThread(new LoginSocketThread(this));
    }
#ifdef DEBUG
    iThreadCore->startThread(new DebugUpdate(this));
#endif
}
LoginSocket::~LoginSocket()
{
    while (true)
    {
        Packet *pkt = _data.pop();
        if (pkt)
            delete pkt;
        else
            break;
        tracelog(OPTIMAL, "Clearing request queue... %u req. left", _data.get_size());
    }
}
string LoginSocket::getJsonParamStr(string &data, string param)
{
    param += "\":\"";
    std::size_t begin_pos = data.find(param);
    if (begin_pos == string::npos)
        return "";
    begin_pos += param.length();
    std::size_t end_pos = data.find("\",", begin_pos);
    if (end_pos == string::npos)
        return "";
    if (end_pos - begin_pos >= 512 || (end_pos - begin_pos) <= 1)
        return "";
    return data.substr(begin_pos, end_pos - begin_pos);
}
string LoginSocket::getJsonParamInt(string &data, string param)
{
    param += "\":";
    std::size_t begin_pos = data.find(param);
    if (begin_pos == string::npos)
        return "";
    begin_pos += param.length();
    std::size_t end_pos = data.find(",", begin_pos);
    if (end_pos == string::npos)
        return "";
    if (end_pos - begin_pos >= 512 || (end_pos - begin_pos) <= 1)
        return "";
    return data.substr(begin_pos, end_pos - begin_pos);
}
string LoginSocket::getParam(string &data, string param)
{
    param += "=";
    std::size_t begin_pos = data.find(param);
    if (begin_pos == string::npos)
        return "";
    begin_pos += param.length();
    std::size_t end_pos = data.find("&", begin_pos);
    if (end_pos == string::npos)
        return "";
    if (end_pos - begin_pos >= 512 || (end_pos - begin_pos) <= 1)
        return "";
    return data.substr(begin_pos, end_pos - begin_pos);
}
string LoginSocket::vkReq(string &data)
{
    string viewer_id 	= getParam(data, "viewer_id");
    string api_id 	= getParam(data, "api_id");
    string auth_key 	= getParam(data, "auth_key");
    string user_id 	= getParam(data, "user_id");
    string referrer 	= getParam(data, "referrer");
    string api_url 	= getParam(data, "api_url");
    string secret 	= getParam(data, "secret");
    string sid 		= getParam(data, "sid");
    string lc_name 	= getParam(data, "lc_name");
    string api_result 	= getParam(data, "api_result");
    api_result 		= UrlDecodeString(api_result);
	
    string first_name  	= getJsonParamStr(api_result, "first_name");
    string last_name  	= getJsonParamStr(api_result, "last_name");
    string nickname  	= getJsonParamStr(api_result, "nickname");
    int sex  		= atoi(getJsonParamInt(api_result, "sex").c_str());
    string photo_medium = getJsonParamStr(api_result, "photo_medium");
	
    if (viewer_id.empty() || api_id.empty() || _social_net[SocialNetDesc::VK].app_id != api_id)
    {
        traceerr("%s, trace req. data: %s", "Error wrong req parameters, Warning!Possible hacking attempt!", data.c_str());
        return "";
    }
    char hash[(MD5_DIGEST_LENGTH+2)*2] = {"\0"};
    getMD5((char*)(api_id + string("_") + viewer_id + string("_") + _social_net[SocialNetDesc::VK].app_secret).c_str(), hash);

    string hash_str = string(hash);
    if (auth_key != hash_str)
    {
        traceerr("%s, trace req. auth_key: %s; local_hash: %s", "Error auth_key fail, Warning!Possible hacking attempt!", auth_key.c_str(), hash_str.c_str());
        return "";
    }

    uint32 vid = atoi(viewer_id.c_str());
    shared_ptr<User> user = iStorage->getLocalUser(vid, SocialNetDesc::VK);
    user->set("first_name", first_name);
    user->set("last_name", last_name);
    user->set("nickname", nickname);
    user->set("avatar", photo_medium);
    user->set("sex", sex);

    //GENERATE NEADED FLASHVARS
    string iframe = _social_net[SocialNetDesc::VK].iframe;
    char flashvars[1024] = {'\0'};

    snprintf(flashvars, 1024, "api_id: \"%s\",viewer_id: \"%s\",user_id: \"%s\", referrer: \"%s\", api_url: \"%s\", secret: \"%s\", sid: \"%s\", lc_name:\
	    \"%s\"",
             api_id.c_str(), viewer_id.c_str(), user_id.c_str(), referrer.c_str(),
             api_url.c_str(), secret.c_str(), sid.c_str(), lc_name.c_str());

    string::size_type pos = iframe.find("var flashvars = {");
    if (pos == string::npos)
    {
        traceerr("%s", "Error: wrong VK template!");
        return "";
    }
    iframe.insert(pos+17, flashvars);

    return iframe;
}
string LoginSocket::okReq(string &data)
{
    return "";
}
string LoginSocket::mmReq(string &data)
{
    return "";
}
string LoginSocket::fbReq(string &data)
{
    return "";
}
string LoginSocket::statReq(string &data)
{
    uint time = iStorage->getCurrentTime();
    uint users_count = iStorage->getLocalUsersCount();
    char ret_val[262144] = {"\0"};
    snprintf(ret_val, 262144,  "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"\
/><title>Статистика</title></head><body>Статистика:<br>Время: %u; <br>Онлайн: %u;</body></html>", time, users_count);
    return ret_val;
}
void LoginSocket::performPacket( Packet *pkt )
{
    string ret_val = "";
    string data = string(pkt->data, pkt->data_size);
    for (int i = 0; i < SocialNetDesc::MAX_SOC; ++i)
    {
        if (data.find(_social_net[i].login_path) != string::npos)
        {
            ret_val = (this->*_social_net[i].handler)(data);
            break;
        }
    }
    if (ret_val.empty())
    {
        if (data.find("GET /voodoo3_stat?secret=power") != string::npos)///stat request
        {
            ret_val = statReq(data);
        }
    }
    pkt->sock->send(ret_val.c_str(), ret_val.length());
    pkt->sock->disconnect();
}
void LoginSocketThread::run()
{
    Packet* pkt = NULL;
    while (_running)
    {
        if (pkt != NULL)
        {
            _owner->performPacket( pkt );
            delete pkt;
        }

        pkt = _owner->_data.pop( );
        if (pkt == NULL)
            sleep(1);
    }
    _running = !_running;
}
void LoginSocketThread::onShutdown()
{
    _running = false;
    while (!_running) {
        sleep(1);
    }
}
LoginSocketThread::LoginSocketThread(LoginSocket *p_owner) : _owner(p_owner), _running(true)
{
}
LoginSocketThread::~LoginSocketThread()
{
}
