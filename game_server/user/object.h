#ifndef OBJECT_H
#define OBJECT_H

#include "common.h"
#include "dict_manager.h"

class Value;

class Object
{
public:
    static Object createLocation(int id);
    static Object createItem(int id);
    static Object createBoss(int id);
    static Object createEmpty(int id);
    static Object createMessage(int id);
    virtual ~Object() {};
    Value* get(string key);
    void set(string key, Value val);
    
    void setDict(DictObject *dict){ _dict = dict;};
    DictObject *getDict(){ return _dict; };
    
    associative_container< string, Value >::iterator getBeginIterator();
    associative_container< string, Value >::iterator getEndIterator();
    Object() {};
private:

    DictObject* _dict;
    associative_container< string, Value > _values;
};

#endif // OBJECT_H
