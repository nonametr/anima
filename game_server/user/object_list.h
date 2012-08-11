#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "object.h"
#include "json.h"
#include "json_value.h"

class Value;

class ObjectList
{
public:
    void deserialize(string init_str);
    JSONValue* serialize();
    void erase(int id);
    void clear();
    void add(int id, Object obj);
    Object* get(int id);
    bool isExist(int id, int count = 0);

    void commit() { _need_commit = true; _sql_need_commit = true; };
    void commitDone() { _need_commit = false; };
    bool needCommit() { return _need_commit; }

    void sqlCommitDone() { _sql_need_commit = false; };
    bool sqlNeedCommit() { return _sql_need_commit; }
    
    associative_container< int, Object >::iterator begin() 	{ return _object_list.begin(); }
    associative_container< int, Object >::iterator end() 	{ return _object_list.end(); }
private:
  
    void _deserializeObjectList();
    void _serializeObjectList();
    
    JSONValue _serialized_obj;
    associative_container< int, Object > _object_list;
    string _serialized_str;
    bool _need_commit;
    bool _sql_need_commit;
};

#endif // OBJECT_LIST_H
