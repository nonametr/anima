#ifndef SHARD_DATA_H
#define SHARD_DATA_H

#include "singleton.h"
#include "common.h"
#include "user.h"
#include "user_ext.h"
#include "storage_thread.h"
#include "storage_timer.h"
#include "socket.h"

#define ONLINE_USER_HASH_SIZE 100
#define USER_HASH_SIZE 1000
///Shard data storage
class Storage : public Singleton<Storage>
{
  friend class StorageThread;
  friend class StorageTimer;
public:
    Storage();
    virtual ~Storage();
    uint32 getCurrentTime(){ return _time; };
    shared_ptr<User> getLocalUser(long long int soc_id, int soc_net_id);
    shared_ptr<User> getLocalUser(uint32 uid);
    shared_ptr<User> getOnlineUser(SOCKET sock);
    void addOnlineUser(SOCKET sock, shared_ptr<User> user);
    shared_ptr<UserExt> getExtUser(uint32 uid);
    shared_ptr<UserInterface> getUser ( uint32 uid );
    int getLocalUsersCount();
private:
    shared_ptr<User> loadUser(uint32 uid);
    void addUser(shared_ptr<User> user);
    shared_ptr<User> findUser(uint32 uid);
    void removeUser(uint32 uid);
    shared_ptr<User> getNewUser(long long int soc_id, uint32 soc_net_id);
    void createUserData(long long int soc_id, uint32 soc_net_id, uint32 uid);
    uint32 createUserLogin(long long int soc_id, uint32 soc_net_id);
    
    associative_container< SOCKET, shared_ptr<User> > _online_users[ONLINE_USER_HASH_SIZE];
    Mutex _online_users_hash_lock[ONLINE_USER_HASH_SIZE];
    
    associative_container< uint, shared_ptr<User> > _users[USER_HASH_SIZE];
    Mutex _users_hash_lock[USER_HASH_SIZE];
    
    uint32 _time;
};

#define iStorage Storage::getSingletonPtr()

#endif // SHARD_DATA_H
