#include "value.h"
#include "dict_object.h"
#include "exeption.h"

DictObject *Value::getDictObject()
{
    return iDictManager->getNamedObject(str_val);
}
string &Value::getString()
{
//     if (type != STRING)
//         traceerr("Wrong type requested - STRING");
    return str_val;
}
int &Value::getInt()
{
//     if (type != INT)
//         traceerr("Wrong type requested - INT");
    return i32;
}
Value::Value()
{}
Value::Value(int val):type(INT), d64(0.0)
{
    i32 = val;
}
Value::Value(string val):type(STRING), d64(0.0)
{
    str_val = val;
}
Value::Value(const char* val):type(STRING), d64(0.0)
{
    str_val = val;
}
