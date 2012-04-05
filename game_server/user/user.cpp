#include "user.h"
#include "command_structs.h"
#include "json.h"
#include "json_value.h"
#include "storage.h"

User::User() : joined(false), _last_activity(0)
{

}
User::~User()
{

}
void User::deserializeObjects()
{
    const string &js_str = _values["items"].toStr();
    JSONValue *val = JSON::parse(js_str.c_str());
    if(!val)
      return;
    uint id;
    uint count;

    JSONArray js_arr = val->asArray();
    for (uint i = 0; i < js_arr.size(); ++i)
    {
        JSONObject js_obj = js_arr[i]->asObject();
        id = (uint)js_obj["id"]->asNumber();
        count = (uint)js_obj["count"]->asNumber();
        _objects[id].setCount(count);
        _objects[id].setId(id);
    }
    delete val;
}
void User::serializeObjects()
{
    string json;
    JSONArray js_arr;
    for (auto it = _objects.begin(); it != _objects.end(); ++it)
    {
        JSONObject js_obj;
        js_obj["id"] = new JSONValue((double)it->second.getId());
        js_obj["count"] = new JSONValue((double)it->second.getCount());
	js_arr.push_back(new JSONValue(js_obj));
    }
    _values["items"] = Value(JSON::stringify(new JSONValue(js_arr)));
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
void User::set(string key, Value value)
{
    _last_activity = iStorage->getCurrentTime();
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
///-----------CLIENT_SYNC---------------
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

