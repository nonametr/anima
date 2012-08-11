#include "login_socket.h"
#include "server.h"
#include "storage.h"
#include "debug_update.h"
#include "urlencode.h"

void LoginSocket::updateDb()
{
    Field *field;

    shared_ptr<QueryResult> qres_social ( iDBManager->getSSDatabase()->queryNA ( DB_SELECT_SOCIAL_NET_SQL ) );
    if ( !qres_social.get() )
    {
        traceerr ( "%s", "Error fetching social network configuration data from DB!" );
        exit ( 1 );
    }
    do
    {
        field = qres_social->fetch();
        int soc_net_id = field[0].getUInt32();
        _social_net[soc_net_id].app_id 	= field[1].getString();
        _social_net[soc_net_id].app_secret 	= field[2].getString();
        _social_net[soc_net_id].login_path 	= field[3].getString();
        _social_net[soc_net_id].iframe 	= field[4].getString();
        _social_net[soc_net_id].iframe_fr_req 	= field[5].getString();
    }
    while ( qres_social->nextRow() );
}
LoginSocket::LoginSocket ( const char *listen_address, uint32 port ) : ListenSocket ( listen_address, port )
{
    updateDb();
    _social_net[SocialNetDesc::VK].handler = &LoginSocket::vkReq;
    _social_net[SocialNetDesc::OK].handler = &LoginSocket::okReq;
    _social_net[SocialNetDesc::MM].handler = &LoginSocket::mmReq;
    _social_net[SocialNetDesc::FB].handler = &LoginSocket::fbReq;

    uint32 num_threads = iServer->getNumWorkerThreads();
    for ( uint32 i = 0; i < num_threads; ++i )
    {
        iThreadCore->startThread ( new LoginSocketThread ( this ) );
    }
#ifdef DEBUG
    iThreadCore->startThread ( new DebugUpdate ( this ) );
#endif
}
LoginSocket::~LoginSocket()
{
    while ( true )
    {
        Packet *pkt = _data.pop();
        if ( pkt )
            delete pkt;
        else
            break;
        tracelog ( OPTIMAL, "Clearing request queue... %u req. left", _data.get_size() );
    }
}
string LoginSocket::okReq ( string &data )
{
    return "";
}
string LoginSocket::mmReq ( string &data )
{
    return "";
}
string LoginSocket::fbReq ( string &data )
{
    return "";
}
void LoginSocket::performPacket ( Packet *pkt )
{
    string ret_val = "";
    try
    {
        for ( int i = 0; i < SocialNetDesc::MAX_SOC; ++i )
        {
            if ( pkt->data.find ( _social_net[i].login_path ) != string::npos )
            {
                ret_val = ( this->*_social_net[i].handler ) ( pkt->data );
                break;
            }
        }
        if ( ret_val.empty() )
        {
            if ( pkt->data.find ( "POST /voodoo3_vk_friends_data" ) != string::npos )
            {
                ret_val = cbFriendsVk ( pkt->data );
            }
	    else if ( pkt->data.find ( "GET /voodoo3_stat?secret=power&" ) != string::npos ) ///stat request
            {
                ret_val = statReq ( pkt->data );
            }
            else if ( pkt->data.find ( "POST /voodoo3_stat?secret=power&" ) != string::npos ) ///stat request
            {
                ret_val = statReq ( pkt->data );
            }
            else if ( pkt->data.find ( "GET /voodoo3_dict_regenerate&" ) != string::npos )
            {
                ret_val = dictRegenerate ( pkt->data );
            }
        }
    }
    catch ( ... )
    {
        traceerr ( "Error, exeption was generated!" );
    }
//     FILE *pFile;
//     pFile = fopen("test.txt", "r+");
//     
//     fseek (pFile , 0 , SEEK_END);
//     int lSize = ftell (pFile);
//     rewind (pFile);
//     
//     char *buf = new char[lSize];
//     fread (buf, 1, lSize, pFile);
//     
//     ret_val = buf;
    ret_val = HTML_HEADER + intToString(ret_val.length()) + "\r\n\r\n" + ret_val;
    pkt->sock->send ( ret_val.c_str(), ret_val.length() );
    pkt->sock->disconnect();
}
void LoginSocketThread::run()
{
    Packet *pkt = NULL;
    while ( _running )
    {
        if ( pkt != NULL )
        {
            _owner->performPacket ( pkt );
            delete pkt;
        }

        pkt = _owner->_data.pop();
        if ( pkt == NULL )
            sleep ( 1 );
    }
    _running = !_running;
}
void LoginSocketThread::onShutdown()
{
    _running = false;
    while ( !_running )
    {
        sleep ( 1 );
    }
}
LoginSocketThread::LoginSocketThread ( LoginSocket *p_owner ) : _owner ( p_owner ), _running ( true )
{
}
LoginSocketThread::~LoginSocketThread()
{
}




