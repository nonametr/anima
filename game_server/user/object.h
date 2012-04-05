#ifndef OBJECT_H
#define OBJECT_H

#include "common.h"

class Object
{
public:
    Object();
    virtual ~Object();
    void setId(uint id) { _id = id; };
    void setCount(uint count) { _count = count; };
    uint getId(){ return _id; };
    uint getCount(){ return _count; };
private:
    uint _id;
    uint _count;
};

#endif // OBJECT_H
