#ifndef SHARD_DATA_H
#define SHARD_DATA_H

#include "../../shared/singleton.h"
#include "../../shared/common.h"
#include "../user/user.h"
#include "../user/user_ext.h"

///Shard data storage
class Storage : public Singleton<Storage>
{
public:
    Storage();
    virtual ~Storage();
    shared_ptr<User> getLocalUser( uint32 uid)
    {
        return shared_ptr<User>();
    }
    shared_ptr<UserExt> getExtUser( uint32 uid)
    {
        return shared_ptr<UserExt>();
    }
    shared_ptr<UserInterface> getUser ( uint32 uid )
    {
        auto it_us = _users.find ( uid );
        if ( it_us != _users.end() )
            return it_us->second;
        else
            return shared_ptr<User>();
    }
private:
    associative_container< uint, shared_ptr<User> > _users;
};

#define iShardData ShardData::getSingletonPtr()

#endif // SHARD_DATA_H
