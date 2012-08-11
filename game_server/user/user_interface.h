#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "common.h"
#include "value.h"

class UserInterface
{

public:
    UserInterface() {};
    virtual ~UserInterface() {};
///--------------SETTERS----------------
    virtual void set(string key, Value value) = 0;
///-------------GETTERS-----------------
    virtual Value* get(string key) = 0;
};

#endif // USER_INTERFACE_H
