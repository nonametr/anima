#ifndef USER_H
#define USER_H

#include "user_interface.h"
#include "common.h"
#include "value.h"
#include "socket.h"

class User : public UserInterface
{
public:
    User();
    virtual ~User();
    void onSessionClose() {};
    void join(Socket *sock);
///-------INTERFACE REALIZATION---------
///--------------SETTERS----------------
    virtual void set(string key, Value &value);
    void set(string key, float value){ Value val = Value::create(value); set(key, val); };
    void set(string key, int value){ Value val = Value::create(value); set(key, val); };
    void set(string key, long long int value){ Value val = Value::create(value); set(key, val); };
    void set(string key, string value){ Value val = Value::create(value); set(key, val); };
///-------------GETTERS-----------------
    virtual Value get(string key);
    void updateClient();
    associative_container< string, Value >::iterator getBeginIterator(){ return _values.begin(); }
    associative_container< string, Value >::iterator getEndIterator(){ return _values.end(); }
private:
    associative_container< string, Value > _values;
    bool joined;
    Socket *_sock;
};

#endif // USER_H
