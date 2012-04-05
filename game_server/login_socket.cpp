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
    if (end_pos - begin_pos >= 512 || (end_pos - begin_pos) < 1)
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
    if (user == shared_ptr<User>())
    {
        traceerr("Error! Requested user not found!");
        return "";
    }
    user->set("first_name", Value(first_name, true));
    user->set("last_name", Value(last_name, true));
    user->set("nickname", Value(nickname, true));
    user->set("avatar", Value(photo_medium, true));
    user->set("sex", Value(sex, true));
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
    string secret 	= getParam(data, "secret");
    string commit_user  = getParam(data, "commit_user");
    string uid 		= getParam(data, "uid");

    if (secret != "power")
    {
        traceerr("Access denied! secret rq = %s", secret.c_str());
        return "";
    }

    uint time = iStorage->getCurrentTime();
    uint users_count = iStorage->getLocalUsersCount();
    string ret_val("");
    char buf[2048] = {"\0"};
    snprintf(buf, 2048,  "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"\
/><title>Статистика</title></head><body>Статистика:<br>Время: %u; <br>Онлайн: %u;", time, users_count);
    ret_val += buf;
    if (!commit_user.empty() && !uid.empty())
    {
        int i_uid = atoi(uid.c_str());
        shared_ptr<User> usr = iStorage->getLocalUser(i_uid);
        if (usr != shared_ptr<User>())
        {
            string param;
            for (auto it = usr->getBeginIterator(); it != usr->getEndIterator(); ++it)
            {
                if (param == "uid")
                    continue;
                param = getParam(data, it->first);
                if (!param.empty())
                {
                    switch (it->second.type)
                    {
                    case Value::STRING:
                        usr->set(it->first, param);
                        break;
                    case Value::INT:
                        usr->set(it->first, atoi(param.c_str()));
                        break;
                    case Value::INT64:
                        usr->set(it->first, atoll(param.c_str()));
                        break;
                    case Value::FLOAT:
                        usr->set(it->first, (float)atof(param.c_str()));
                        break;
                    case Value::DOUBLE:
                        usr->set(it->first, (float)atof(param.c_str()));
                        break;
                    case Value::UNKNOWN:
                    default:
                        break;
                    }
                }
            }
        }
    }
    else if (!uid.empty())
    {
        int i_uid = atoi(uid.c_str());
        shared_ptr<User> usr = iStorage->getLocalUser(i_uid);
        if (usr != shared_ptr<User>())
        {
            ret_val += "<div style=\"text-align:left;\">\
		    <form action=\"http://31.43.122.45/voodoo3_stat?secret=power&\", method=\"POST\">\
		    <table>\
		    <tr><td><input type=\"hidden\" name=\"commit_user\" value=\"true\"/></td></tr>";
            for (auto it = usr->getBeginIterator(); it != usr->getEndIterator(); ++it)
            {
                switch (it->second.type)
                {
                case Value::STRING:
                    snprintf(buf, 2048,  "<tr><td>%s</td><td> <input type=\"text\" name=\"%s\" value=\"%s\"/><br /></td></tr>", it->first.c_str(),
                             it->first.c_str(), it->second.toStr().c_str());
                    break;
                case Value::INT:
                    snprintf(buf, 2048,  "<tr><td>%s</td><td> <input type=\"text\" name=\"%s\" value=\"%i\"/><br /></td></tr>", it->first.c_str(),
                             it->first.c_str(), it->second.toInt());
                    break;
                case Value::INT64:
                    snprintf(buf, 2048,  "<tr><td>%s</td><td> <input type=\"text\" name=\"%s\" value=\"%lli\"/><br /></td></tr>", it->first.c_str(),
                             it->first.c_str(), it->second.toInt64());
                    break;
                case Value::FLOAT:
                    snprintf(buf, 2048,  "<tr><td>%s</td><td> <input type=\"text\" name=\"%s\" value=\"%f\"/><br /></td></tr>", it->first.c_str(),
                             it->first.c_str(), it->second.toFloat());
                    break;
                case Value::DOUBLE:
                    snprintf(buf, 2048,  "<tr><td>%s</td><td> <input type=\"text\" name=\"%s\" value=\"%f\"/><br /></td></tr>", it->first.c_str(),
                             it->first.c_str(), it->second.toDouble());
                    break;
                case Value::UNKNOWN:
                default:
                    break;
                }

                ret_val += buf;
            }

            ret_val += "</table><input type=\"submit\" value=\"Сохранить\">\
		    </form>";
        }
    }
    ret_val += "</body></html>";
    return ret_val;
}
JSONValue* sqlToJson(shared_ptr<QueryResult> &qres)
{
    JSONArray js_arr;
    Field *field;
    do
    {
        JSONObject js_obj;
        field = qres->fetch();
        for (uint32 i = 0; i < qres->getFieldCount(); ++i)
        {
            switch (field[i].getType())
            {
            case MYSQL_TYPE_DECIMAL:
            case MYSQL_TYPE_TINY:
            case MYSQL_TYPE_SHORT:
            case MYSQL_TYPE_LONG:
            case MYSQL_TYPE_NULL:
            case MYSQL_TYPE_TIMESTAMP:
            case MYSQL_TYPE_LONGLONG:
            case MYSQL_TYPE_INT24:
                js_obj[field[i].getFieldName()] = new JSONValue((double)field[i].getUInt32());
                break;
            case MYSQL_TYPE_FLOAT:
            case MYSQL_TYPE_DOUBLE:
                js_obj[field[i].getFieldName()] = new JSONValue((double)field[i].getFloat());
                break;
            case MYSQL_TYPE_DATE:
            case MYSQL_TYPE_TIME:
            case MYSQL_TYPE_DATETIME:
            case MYSQL_TYPE_YEAR:
            case MYSQL_TYPE_NEWDATE:
            case MYSQL_TYPE_VARCHAR:
            case MYSQL_TYPE_BIT:
            case MYSQL_TYPE_NEWDECIMAL:
            case MYSQL_TYPE_ENUM:
            case MYSQL_TYPE_SET:
            case MYSQL_TYPE_TINY_BLOB:
            case MYSQL_TYPE_MEDIUM_BLOB:
            case MYSQL_TYPE_LONG_BLOB:
            case MYSQL_TYPE_BLOB:
            case MYSQL_TYPE_VAR_STRING:
            case MYSQL_TYPE_STRING:
            case MYSQL_TYPE_GEOMETRY:
                js_obj[field[i].getFieldName()] = new JSONValue(field[i].getString());
                break;
            default:
                break;
            }
        }
        js_arr.push_back(new JSONValue(js_obj));
    }
    while ( qres->nextRow() );
    return new JSONValue(js_arr);
}
string LoginSocket::dictRegenerate(string &data)
{
    string ret;

    shared_ptr<QueryResult> qres_dict_boss ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_BOSS) );
    shared_ptr<QueryResult> qres_dict_lang( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_LANG) );
    shared_ptr<QueryResult> qres_dict_location( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_LOCATION) );
    shared_ptr<QueryResult> qres_dict_object( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_OBJECT) );
    shared_ptr<QueryResult> qres_dict_pack( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_PACK) );
    shared_ptr<QueryResult> qres_dict_shop( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_SHOP) );
    if ( !qres_dict_boss.get() || !qres_dict_lang.get() || !qres_dict_location.get() || !qres_dict_object.get() || !qres_dict_pack.get() ||
            !qres_dict_shop.get())
    {
        traceerr("%s, db = %u, dl = %u, dloc = %u, do = %u, dp = %u, ds = %u", "Error fetching dict data from DB!", (uint)qres_dict_boss.get(),
                 (uint)qres_dict_lang.get(), (uint)qres_dict_location.get(), (uint)qres_dict_object.get(), (uint)qres_dict_pack.get(),
(uint)qres_dict_shop.get());
        return "";
    }

    JSONObject js_obj;
    js_obj["dict_boss"] 	= sqlToJson(qres_dict_boss);
    js_obj["dict_object"] 	= sqlToJson(qres_dict_object);
    js_obj["dict_lang"] 	= sqlToJson(qres_dict_lang);
    js_obj["dict_location"] 	= sqlToJson(qres_dict_location);
    js_obj["dict_pack"] 	= sqlToJson(qres_dict_pack);
    js_obj["dict_shop"] 	= sqlToJson(qres_dict_shop);

    JSONValue *js_val = new JSONValue(js_obj);
    ret = "ALL DICTIONARIES REGENERATED SUCCESSFULLY! ====>   " + JSON::stringify(js_val);
    delete js_val;

    return ret;
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
        if (data.find("GET /voodoo3_stat?secret=power&") != string::npos)///stat request
        {
            ret_val = statReq(data);
        }
        else if (data.find("POST /voodoo3_stat?secret=power&") != string::npos)///stat request
        {
            ret_val = statReq(data);
        }
        else if (data.find("GET /voodoo3_dict_regenerate&") != string::npos)
        {
            ret_val = dictRegenerate(data);
        }
    }
    ret_val = HTML_HEADER + ret_val;
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


