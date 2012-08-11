#include "object.h"
#include "value.h"

Object Object::createLocation(int id)
{
    DictObject*dict = iDictManager->getObject(id);
    Object ret_val;
    ret_val._dict 			= dict;
    ret_val._values["id"] 		= id;
    ret_val._values["master_end_time"]  = 0;
    ret_val._values["lvl_on_work"] 	= 1;
    return ret_val;
}
Object Object::createBoss(int id)
{
    DictObject*dict = iDictManager->getObject(id);
    Object ret_val;
    ret_val._dict 			= dict;
    return ret_val;
}
Object Object::createEmpty(int id)
{
    Object ret_val;
    return ret_val;
}
Object Object::createMessage(int id)
{
    Object ret_val;
    ret_val.set("id", id);
    return ret_val;
}
Object Object::createItem(int id)
{
    DictObject*dict = iDictManager->getObject(id);
    Object ret_val;
    ret_val._dict 		= dict;
    ret_val._values["count"] 	= 1;
    ret_val._values["id"] 	= id;
    return ret_val;
}
Value* Object::get(string key)
{
    auto it = _values.find(key);
    if (it == _values.end())
         ErrorExeption(ErrorExeption::VALUE_NOT_FOUND_IN_OBJECT, intToString(__LINE__)+string(" ")+ string(__FUNCTION__));
    return &it->second;
}
void Object::set(string key, Value val)
{
  _values[key] = val;
}
associative_container< string, Value >::iterator Object::getBeginIterator()
{
    return _values.begin();
}
associative_container< string, Value >::iterator Object::getEndIterator()
{
    return _values.end();
}
