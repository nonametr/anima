#include "dict_object.h"

Value* DictObject::get(string key)
{
    auto it = _values.find(key);
    if ( it != _values.end() )
        return &it->second;
     ErrorExeption(ErrorExeption::ID_NOT_FOUND_IN_DICT, intToString(__LINE__)+string(" ")+ string(__FUNCTION__));
    exit(0);
}
