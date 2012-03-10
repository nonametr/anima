#include "user.h"

User::User()
{

}
User::~User()
{

}
///--------------SETTERS----------------
void User::set(string key, Value &value)
{
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
string User::getUpdate()
{
    string res("");
    for (auto it = _values.begin(); it != _values.end(); ++it)
    {
        if (it->second.need_update)
        {
            switch (it->second.type)
            {
            case Value::STRING:
                res += it->first + " = "+ it->second.str_val + ", ";
                break;
            case Value::INT:
                res += it->first + " = "+ intToString(it->second.i32) + ", ";
                break;
            case Value::INT64:
                res += it->first + " = "+ int64ToString(it->second.i64) + ", ";
                break;
            case Value::FLOAT:
                res += it->first + " = "+ floatToString(it->second.f32) + ", ";
                break;
            case Value::DOUBLE:
                res += it->first + " = "+ doubleToString(it->second.d64) + ", ";
                break;
            default:
                break;
            }
        }
    }
    res.erase(res.length() - 1, 1);
    return res;
}
