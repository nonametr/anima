#ifndef DICT_OBJECT_H
#define DICT_OBJECT_H

#include "common.h"
#include "value.h"

class DictObject
{
    friend class DictManager;
public:
    OBJECT_TYPES type;
    Value* get(string key);
    uint &getId() 
    {
        return _id;
    }
    string &getName() 
    {
        return _values["object"].getString();
    }
private:
    uint _id;
    associative_container<string, Value> _values;
};
#endif // DICT_OBJECT_H
