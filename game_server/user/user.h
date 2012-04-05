#ifndef USER_H
#define USER_H

#include "user_interface.h"
#include "common.h"
#include "value.h"
#include "socket.h"
#include "object.h"

class User : public UserInterface
{
public:
    User();
    virtual ~User();
    void onSessionClose() {};
    void join(Socket *sock);
///-------INTERFACE REALIZATION---------
///--------------SETTERS----------------
    virtual void set(string key, Value value);
    void set(string key, float value)		{ set(key, Value(value)); };
    void set(string key, int value)		{ set(key, Value(value)); };
    void set(string key, long long int value)	{ set(key, Value(value)); };
    void set(string key, string value)		{ set(key, Value(value)); };
///-------------GETTERS-----------------
    virtual Value get(string key);
    uint getLastActivity(){ return _last_activity; };
    void updateClient();
    void deserializeObjects();
    void serializeObjects();
    associative_container< string, Value >::iterator getBeginIterator(){ return _values.begin(); }
    associative_container< string, Value >::iterator getEndIterator(){ return _values.end(); }
private:
    associative_container< string, Value > _values;//map< param_name, param_value>
    associative_container< uint, Object> _objects;//map< id, Object>
    bool joined;
    Socket *_sock;
    uint _last_activity;
};

#endif // USER_H
