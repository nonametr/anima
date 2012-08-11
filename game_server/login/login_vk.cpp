#include "login_socket.h"
#include "server.h"
#include "storage.h"
#include "debug_update.h"
#include "urlencode.h"

string LoginSocket::vkReq ( string &data )
{
    //GENERATE NEADED FLASHVARS
    string iframe;
    string viewer_id 	= getParam ( data, "viewer_id" );

    if ( viewer_id.empty() )
    {
        traceerr ( "%s, trace req. data: %s", "Error wrong req parameters, Warning!Possible hacking attempt!", data.c_str() );
        return "";
    }

    uint32 vid = atoi ( viewer_id.c_str() );
    User *user = iStorage->getLocalUser ( vid, SocialNetDesc::VK );
    if ( user == NULL )
    {
        traceerr ( "Error! Requested user not found!" );
        return "";
    }

    user->lock();
//     int last_join = user->get ( "last_join_utime" )->getInt();
//     user->set("last_join_utime", iStorage->getCurrentTime());
//     if ( last_join < iStorage->getCurrentTime() - 3600 )
//     {
//         string api_result 	= getParam ( data, "api_result" );
//         api_result 		= UrlDecodeString ( api_result );
//         string first_name  	= getJsonParamStr ( api_result, "first_name" );
//         string last_name  	= getJsonParamStr ( api_result, "last_name" );
//         string nickname  	= getJsonParamStr ( api_result, "nickname" );
//         int sex  		= atoi ( getJsonParamInt ( api_result, "sex" ).c_str() );
//         string photo_medium 	= getJsonParamStr ( api_result, "photo_medium" );
//         user->set ( "first_name", first_name );
//         user->set ( "last_name", last_name );
//         user->set ( "nickname", nickname );
//         user->set ( "avatar", photo_medium );
//         user->set ( "sex", sex );
//         iframe = _social_net[SocialNetDesc::VK].iframe_fr_req;
//     }
//     else
        iframe = getGameVKIFrame ( data );
    user->unlock();
    return iframe;
}
string LoginSocket::getGameVKIFrame ( string &data )
{
    string viewer_id 	= getParam ( data, "viewer_id" );
    string api_id 	= getParam ( data, "api_id" );
    string auth_key 	= getParam ( data, "auth_key" );
    string user_id 	= getParam ( data, "user_id" );
    string referrer 	= getParam ( data, "referrer" );
    string api_url 	= getParam ( data, "api_url" );
    string secret 	= getParam ( data, "secret" );
    string sid 		= getParam ( data, "sid" );
    string lc_name 	= getParam ( data, "lc_name" );
    string api_result 	= getParam ( data, "api_result" );
    api_result 		= UrlDecodeString ( api_result );

    if ( viewer_id.empty() || api_id.empty() || _social_net[SocialNetDesc::VK].app_id != api_id )
    {
        traceerr ( "%s, trace req. data: %s", "Error wrong req parameters, Warning!Possible hacking attempt!", data.c_str() );
        return "";
    }
    char hash[ ( MD5_DIGEST_LENGTH + 2 ) * 2] = {"\0"};
    getMD5 ( ( char * ) ( api_id + string ( "_" ) + viewer_id + string ( "_" ) + _social_net[SocialNetDesc::VK].app_secret ).c_str(), hash );

    string hash_str = string ( hash );
    if ( auth_key != hash_str )
    {
        traceerr ( "%s, trace req. auth_key: %s; local_hash: %s", "Error auth_key fail, Warning!Possible hacking attempt!", auth_key.c_str(), hash_str.c_str()
                 );
        return "";
    }

    string iframe = _social_net[SocialNetDesc::VK].iframe;
    char flashvars[1024] = {'\0'};

    snprintf ( flashvars, 1024, "api_id: \"%s\",viewer_id: \"%s\",user_id: \"%s\", referrer: \"%s\", api_url: \"%s\", secret: \"%s\", sid: \"%s\", lc_name:\
	    \"%s\"",
               api_id.c_str(), viewer_id.c_str(), user_id.c_str(), referrer.c_str(),
               api_url.c_str(), secret.c_str(), sid.c_str(), lc_name.c_str() );

    string::size_type pos = iframe.find ( "var flashvars = {" );
    if ( pos == string::npos )
    {
        traceerr ( "%s", "Error: wrong VK template!" );
        return "";
    }
    iframe.insert ( pos + 17, flashvars );
    return iframe;
}
string LoginSocket::generateVKAppFriends ( JSONValue *json, uint db_id )
{
    string friends_str ( "" );
    ///Checking for correct struct
    if ( !json->isObject() )
    {
        traceerr ( "wrong friends json" );
        return "[]";
    }
    auto it = json->asObject().find ( "response" );
    if ( it == json->asObject().end() )
    {
        traceerr ( "wrong friends json" );
        return "[]";
    }
    if ( !it->second->isObject() )
    {
        traceerr ( "wrong friends json" );
        return "[]";
    }
    JSONObject friends_js = it->second->asObject();
    for ( auto it = friends_js.begin(); it != friends_js.end(); ++it )
    {
        friends_str += intToString ( ( int ) it->second->asNumber() ) + ",";
    }
    if ( friends_str.empty() )
    {
        traceerr ( "wrong friends json" );
        return "[]";
    }
    friends_str.erase ( friends_str.length() - 1 );
    JSONArray js_arr;
    shared_ptr<QueryResult> qres = shared_ptr<QueryResult> ( iDBManager->getDatabase ( db_id )->query ( DB_GET_UID_LVL_EXP_FROM_USER_RATING_DATA__SOC_ID,
                                   friends_str.c_str() ) );
    if ( qres.get() == NULL )
    {
        traceerr ( "wrong friends json" );
        return "[]";
    }
    do
    {
        JSONObject obj;
        Field *field = qres->fetch();
        obj["uid"] = new JSONValue ( ( double ) field[0].getUInt32() );
        obj["social_id"] = new JSONValue ( ( double ) field[1].getUInt32() );
        obj["lvl"] = new JSONValue ( ( double ) field[2].getUInt32() );
        obj["exp"] = new JSONValue ( ( double ) field[3].getUInt32() );

        js_arr.push_back ( new JSONValue ( obj ) );
    }
    while ( qres->nextRow() );
    JSONValue *js_val = new JSONValue ( js_arr );
    string js_str = JSON::stringify ( js_val );
    delete js_val;
    return js_str;
}
string LoginSocket::cbFriendsVk ( string &data )
{
    std::size_t vk_data_pos = data.find ( "/voodoo3_vk_login?api_url=http://api.vk.com/api.php" );
    std::size_t vk_friends_pos = data.find ( "friends_vk_req_friends_post=" );
    if ( vk_data_pos == string::npos || vk_friends_pos == string::npos )
    {
        traceerr ( "%s, trace req. data: %s", "Error wrong req parameters, Warning!Possible hacking attempt!", data.c_str() );
        return "";
    }
    string vk_data = data.substr ( vk_data_pos, string::npos );
    string vk_friends = data.substr ( vk_friends_pos + strlen ( "friends_vk_req_friends_post=" ), string::npos );

    string viewer_id 	= getParam ( vk_data, "viewer_id" );

    if ( viewer_id.empty() )
    {
        traceerr ( "%s, trace req. data: %s", "Error wrong req parameters, Warning!Possible hacking attempt!", data.c_str() );
        return "";
    }

    uint32 vid = atoi ( viewer_id.c_str() );
    User *user = iStorage->getLocalUser ( vid, SocialNetDesc::VK );
    if ( user == NULL )
        return "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"\
		/><title>Error</title></head><body><h1>Error loading user. User not found!</body></html>";
    else
    {
        string game_iframe = getGameVKIFrame ( vk_data );
        vk_friends = UrlDecodeString ( vk_friends );
        traceerr ( "str = %s", vk_friends.c_str() );
        JSONValue *json = JSON::parse ( vk_friends.c_str() );

        if ( json == NULL )
        {
            traceerr ( "%s", "Can't parce vk friends json" );
            return "";
        }
        user->set ( "app_friends_data", generateVKAppFriends ( json, user->get ( "db_id" )->getInt() ) );
        return game_iframe;
    }
}
