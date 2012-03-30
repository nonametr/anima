#include "user.h"
#include "command_structs.h"
#include "json.h"
#include "json_value.h"

User::User() : joined(false)
{

}
User::~User()
{

}
void User::join(Socket *sock)
{
    _sock 	= sock;
    joined 	= true;

    for (auto it = _values.begin(); it != _values.end(); ++it)
    {
        it->second.need_client_update = true;
    }
}
///--------------SETTERS----------------
void User::set(string key, Value &value)
{
    if (joined)
    {
        value.need_client_update = true;
        value.need_sql_update = true;
    }
    _values[key] = value;
}
///-------------GETTERS-----------------
Value User::get(string key)
{
    auto it = _values.find(key);
    if (it != _values.end())
    {
        return it->second;
    }
    return Value(Value::UNKNOWN);
};
void User::updateClient()
{
    JSONObject json_obj;
    for (auto it = _values.begin(); it != _values.end(); ++it)
    {
        if (it->second.need_client_update)
        {
            switch (it->second.type)
            {
            case Value::STRING:
                json_obj[it->first] = new JSONValue(it->second.toStr());
                break;
            case Value::INT:
                json_obj[it->first] = new JSONValue((double)it->second.toInt());
                break;
            case Value::INT64:
                json_obj[it->first] = new JSONValue((double)it->second.toInt64());
                break;
            case Value::FLOAT:
                json_obj[it->first] = new JSONValue((double)it->second.toFloat());
                break;
            case Value::DOUBLE:
                json_obj[it->first] = new JSONValue((double)it->second.toDouble());
                break;
            case Value::UNKNOWN:
            default:
                break;
            }
            it->second.need_client_update = false;
        }
    }
    JSONValue* val = new JSONValue(json_obj);
    string json = val->stringify();
    Packet client_update_pkt = OG_USER_DATA::create(json);
    _sock->send(&client_update_pkt);
}
