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
  friend class DictManager;
  friend class StorageThread;
  friend class StorageTimer;
public:
    Storage();
    virtual ~Storage();
    
    User* loadLocalUser(SOCKET sock, long long int soc_id, int soc_net_id);
    User* getOnlineUser(SOCKET sock);
    User* getLocalUser(uint32 uid);
    User* getLocalUser(long long int soc_id, int soc_net_id);
    
    static int getCurrentTime(){ return _time; };
    int getLocalUsersCount();
private:    
    void addOnlineUser(SOCKET sock, User* user);
//     shared_ptr<UserExt> getExtUser(uint32 uid);
//     shared_ptr<UserInterface> getUser ( uint32 uid );
    
    User* loadUser(uint32 uid);
    void loadUserData(User* usr, shared_ptr<QueryResult> usr_qres);
    void loadUserObjects(User* usr, shared_ptr<QueryResult> usr_qres);
    void loadUserPrivateObjects(User* usr, shared_ptr<QueryResult> usr_qres);
    
    void addUser(User* user);
    User* findUser(uint32 uid);
    void removeUser(uint32 uid);
    User* getNewUser(long long int soc_id, uint32 soc_net_id);
    void createUserData(long long int soc_id, uint32 soc_net_id, uint32 uid);
    uint32 createUserLogin(long long int soc_id, uint32 soc_net_id);
    
    associative_container< SOCKET, User* > _online_users[ONLINE_USER_HASH_SIZE];
    Mutex _online_users_hash_lock[ONLINE_USER_HASH_SIZE];
    
    associative_container< uint, User* > _users[USER_HASH_SIZE];
    Mutex _users_hash_lock[USER_HASH_SIZE];
    
    static int _time;
};

#define iStorage Storage::getSingletonPtr()

#endif // SHARD_DATA_H
