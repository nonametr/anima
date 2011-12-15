#ifndef SHARD_DATA_H
#define SHARD_DATA_H

#include "../shared/singleton.h"
#include "../shared/common.h"
#include "user.h"
#include "shard_ext.h"

///Shard data storage
class ShardStorage : public Singleton<ShardStorage>
{
public:
    ShardStorage();
    virtual ~ShardStorage();
    shared_ptr<User> getUser ( uint32 uid )
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
