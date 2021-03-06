#ifndef USER_EXT_H
#define USER_EXT_H

#include "user_interface.h"

///This class used to interact with users from other shards
class UserExt : public UserInterface
{

public:
    UserExt(uint32 uid, uint32 server_id);
    virtual ~UserExt();
///--------------SETTERS----------------
    virtual void set(string key, Value value) {};
///-------------GETTERS-----------------
    virtual Value* get(string key) { return new Value; }
private:
    uint32 _uid;
    uint32 _server_id;
};

#endif // USER_EXT_H
