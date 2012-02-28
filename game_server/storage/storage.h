#ifndef SHARD_DATA_H
#define SHARD_DATA_H

#include "singleton.h"
#include "common.h"
#include "user.h"
#include "user_ext.h"

///Shard data storage
class Storage : public Singleton<Storage>
{
public:
    Storage();
    virtual ~Storage();
    shared_ptr<User> createNewUser(long int soc_id, uint32 soc_net_id);
    shared_ptr<User> loadUser(uint32 uid);
    shared_ptr<User> getLocalUser( uint32 uid);
    shared_ptr<UserExt> getExtUser( uint32 uid);
    shared_ptr<UserInterface> getUser ( uint32 uid );
private:
    associative_container< uint, shared_ptr<User> > _users;
};

#define iStorage Storage::getSingletonPtr()

#endif // SHARD_DATA_H
