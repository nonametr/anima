#include "login_socket.h"
#include "server.h"
#include "storage.h"
#include "debug_update.h"
#include "urlencode.h"

string LoginSocket::statReq ( string &data )
{
    string secret 	= getParam ( data, "secret" );
    string commit_user  = getParam ( data, "commit_user" );
    string uid 		= getParam ( data, "uid" );

    if ( secret != "power" )
    {
        traceerr ( "Access denied! secret rq = %s", secret.c_str() );
        return "";
    }

    uint time = iStorage->getCurrentTime();
    uint users_count = iStorage->getLocalUsersCount();
    string ret_val ( "" );
    char buf[20480] = {"\0"};
    snprintf ( buf, 20480,  "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"\
/><title>Статистика</title><link media=\"screen\" href=\"http://www.podari-zhizn.com/templates/Default/style/style.css\" type=\"text/css\" rel=\"stylesheet\" /></head><body>Статистика:<br>Время: %u; <br>Онлайн: %u;", time, users_count );
    ret_val += buf;
    if ( !commit_user.empty() && !uid.empty() )
    {
        int i_uid = atoi ( uid.c_str() );
        User* usr = iStorage->getLocalUser ( i_uid );
        if ( usr != NULL )
        {
            usr->set ( "last_activity", iStorage->getCurrentTime() );
            string param;

            for ( auto it = usr->_values.begin(); it != usr->_values.end(); ++it )
            {
                if ( param == "uid" )
                    continue;
                param = getParam ( data, it->first );
                param = UrlDecodeString ( param );
                if ( !param.empty() )
                {
                    switch ( it->second.type )
                    {
                    case Value::STRING:
                        usr->set ( it->first, param );
                        break;
                    case Value::INT:
                        usr->set ( it->first, atoi ( param.c_str() ) );
                        break;
                    default:
                        break;
                    }
                }
            }
            for ( auto it = usr->_object_lists.begin(); it != usr->_object_lists.end(); ++it )
            {
                param = getParam ( data, it->first );
                param = UrlDecodeString ( param );
                if ( !param.empty() )
                {
                    usr->setObjectList ( it->first, param );

                }
            }
        }
    }
    else if ( !uid.empty() )
    {
        int i_uid = atoi ( uid.c_str() );
        User* usr = iStorage->getLocalUser ( i_uid );
        if ( usr != NULL )
        {
            usr->set ( "last_activity", iStorage->getCurrentTime() );
            ret_val += "<div style=\"text-align:left;\">\
    		    <form action=\"http://31.43.122.45/voodoo3_stat?secret=power&\", method=\"POST\">\
    		    <table width = 100%% class = \"tablead\">\
    		    <tr><td width = 1%%><input type=\"hidden\" name=\"commit_user\" value=\"true\"/></td></tr>";
            for ( auto it = usr->_values.begin(); it != usr->_values.end(); ++it )
            {
                switch ( it->second.type )
                {
                case Value::STRING:
                    snprintf ( buf, 20480,  "<tr><td>%s</td><td> <input type=\"text\" style=\"width: 100%%;\" name=\"%s\" value=\"%s\"/><br /></td></tr>", it->first.c_str(),
                               it->first.c_str(), it->second.getString().c_str() );
                    break;
                case Value::INT:
                    snprintf ( buf, 20480,  "<tr><td>%s</td><td> <input type=\"text\" style=\"width: 100%%;\" name=\"%s\" value=\"%i\"/><br /></td></tr>", it->first.c_str(),
                               it->first.c_str(), it->second.getInt() );
                    break;
                default:
                    break;
                }
                ret_val += buf;
            }
            for ( auto it = usr->_object_lists.begin(); it != usr->_object_lists.end(); ++it )
            {
                snprintf ( buf, 20480,  "<tr><td>%s</td><td> <input type=\"text\" style=\"width: 100%%;\" name=\"%s\" value=\'%s\'/><br /></td></tr>", it->first.c_str(),
                           it->first.c_str(), it->second.serialize()->stringify().c_str() );
                ret_val += buf;
            }
            ret_val += "</table><input type=\"submit\" value=\"Сохранить\">\
    		    </form>";
        }
    }
    ret_val += "</body></html>";
    return ret_val;
}
JSONValue *sqlToJson ( shared_ptr<QueryResult> &qres, bool as_array )
{
    JSONObject js_key_obj;
    Field *field;
    string key_name;
    string val;
    do
    {
        JSONObject js_obj;
        field = qres->fetch();
        for ( uint32 i = 0; i < qres->getFieldCount(); ++i )
        {
            switch ( field[i].getType() )
            {
            case MYSQL_TYPE_DECIMAL:
            case MYSQL_TYPE_TINY:
            case MYSQL_TYPE_SHORT:
            case MYSQL_TYPE_LONG:
            case MYSQL_TYPE_NULL:
            case MYSQL_TYPE_TIMESTAMP:
            case MYSQL_TYPE_LONGLONG:
            case MYSQL_TYPE_INT24:
                js_obj[field[i].getFieldName()] = new JSONValue ( ( double ) field[i].getUInt32() );
                break;
            case MYSQL_TYPE_FLOAT:
            case MYSQL_TYPE_DOUBLE:
                js_obj[field[i].getFieldName()] = new JSONValue ( ( double ) field[i].getFloat() );
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
                if ( string ( field[i].getFieldName() ) == "object" )
                {
                    key_name = field[i].getString();
                }
                else
                    js_obj[field[i].getFieldName()] = new JSONValue ( field[i].getString() );
                break;
            default:
                break;
            }
        }
        if ( as_array )
        {
            if ( js_key_obj.find ( key_name ) != js_key_obj.end() )
            {
                JSONArray arr = js_key_obj[key_name]->asArray();
                arr.push_back ( new JSONValue ( js_obj ) );
                js_key_obj[key_name] = new JSONValue ( arr );
            }
            else
            {
                JSONArray arr;
                arr.push_back ( new JSONValue ( js_obj ) );
                js_key_obj[key_name] = new JSONValue ( arr );
            }
        }
        else
        {
            js_key_obj[key_name] = new JSONValue ( js_obj );
        }
    }
    while ( qres->nextRow() );
    return new JSONValue ( js_key_obj );
}
string LoginSocket::dictRegenerate ( string &data )
{
    string ret;

    shared_ptr<QueryResult> qres_dict_boss ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_BOSS ) );
    shared_ptr<QueryResult> qres_dict_boss_strike ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_BOSS_STRIKE ) );
    shared_ptr<QueryResult> qres_dict_messages ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_MESSAGES ) );
    shared_ptr<QueryResult> qres_dict_ml_interface ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_ML_INTERFACE ) );
    shared_ptr<QueryResult> qres_dict_swf_object ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_SWF_OBJECT ) );
    shared_ptr<QueryResult> qres_dict_lang ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_LANG ) );
    shared_ptr<QueryResult> qres_dict_location ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_LOCATION ) );
    shared_ptr<QueryResult> qres_dict_object ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_OBJECT ) );
    shared_ptr<QueryResult> qres_dict_pack ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_PACK ) );
    shared_ptr<QueryResult> qres_dict_exchange ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_EXCHANGE ) );
    shared_ptr<QueryResult> qres_dict_give ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_GIVE ) );
    shared_ptr<QueryResult> qres_dict_drop_chance ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_DROP_CHANCE ) );
    if ( !qres_dict_boss.get() || !qres_dict_lang.get() || !qres_dict_location.get() || !qres_dict_object.get() || !qres_dict_pack.get() ||
            !qres_dict_exchange.get() || !qres_dict_give.get() )
    {
        traceerr ( "%s", "Error fetching dict data from DB!" );
        return "";
    }

    JSONObject js_obj;
    js_obj["dict_boss"] 	= sqlToJson ( qres_dict_boss, false );
    js_obj["dict_boss_strike"] 	= sqlToJson ( qres_dict_boss_strike, false );
    js_obj["dict_messages"] 	= sqlToJson ( qres_dict_messages, false );
    js_obj["dict_ml_interface"]= sqlToJson ( qres_dict_ml_interface, false );
    js_obj["dict_swf_object"] 	= sqlToJson ( qres_dict_swf_object, false );
    js_obj["dict_object"] 	= sqlToJson ( qres_dict_object, false );
    js_obj["dict_lang"] 	= sqlToJson ( qres_dict_lang, false );
    js_obj["dict_location"] 	= sqlToJson ( qres_dict_location, true );
    js_obj["dict_pack"] 	= sqlToJson ( qres_dict_pack, true );
    js_obj["dict_exchange"] 	= sqlToJson ( qres_dict_exchange, true );
    js_obj["dict_give"] 	= sqlToJson ( qres_dict_give, true );
    js_obj["dict_drop_chance"] 	= sqlToJson ( qres_dict_drop_chance, true );

    JSONValue *js_val = new JSONValue ( js_obj );
    ret = JSON::stringify ( js_val );
    delete js_val;

    logError ( "dict_reg.txt", ret.c_str() );
    return ret;
}
