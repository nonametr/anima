#ifndef VALUE_H
#define VALUE_H

#include "common.h"
#include "object_list.h"

class Value
{
public:
    enum TYPE {STRING, INT} type;

    DictObject *getDictObject();
    string &getString();
    int &getInt();

    void commit() { _need_commit = true; _sql_need_commit = true; };
    void commitDone() { _need_commit = false; };
    bool needCommit() { return _need_commit; }

    void sqlCommitDone() { _sql_need_commit = false; };
    bool sqlNeedCommit() { return _sql_need_commit; }
    
    Value();
    Value(int val);
    Value(string val);
    Value(const char* val);

private:
    string str_val;
    union
    {
        int i32;
        long long int i64;
        float f32;
        double d64;
    };
    bool _need_commit;
    bool _sql_need_commit;
};

#endif // VALUE_H

