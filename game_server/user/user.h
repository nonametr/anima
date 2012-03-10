#ifndef USER_H
#define USER_H

#include "user_interface.h"
#include "common.h"
#include "value.h"

class User : public UserInterface
{
public:
    User();
    virtual ~User();
    void onSessionClose() {};
///-------INTERFACE REALIZATION---------
///--------------SETTERS----------------
    virtual void set(string key, Value &value);
    void set(string key, float value){ Value val = Value::create(value); set(key, val); };
    void set(string key, int value){ Value val = Value::create(value); set(key, val); };
    void set(string key, long long int value){ Value val = Value::create(value); set(key, val); };
    void set(string key, string value){ Value val = Value::create(value); set(key, val); };
///-------------GETTERS-----------------
    virtual Value get(string key);
    string getUpdate();
private:
    associative_container< string, Value > _values;
};

#endif // USER_H
