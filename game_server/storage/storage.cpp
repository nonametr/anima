#include "storage.h"
#include "singleton.h"
#include "game_server.h"
#include "sql_define.h"
#include "ext_server_manager.h"
#include <time.h>
#include <mysql/mysql.h>

initialiseSingleton ( Storage );

Storage::Storage()
{
//      iPeriodicThreadCaller->startPeriodicThread(new StorageThread, UNLOAD_PERIOD);
//      iPeriodicThreadCaller->startPeriodicThread(new StorageTimer, TIME_UPDATE_PERIOD);
}
Storage::~Storage()
{
    for (uint32 i = 0; i < USER_HASH_SIZE; ++i)
    {
        _users_hash_lock[i].lock();
        _users[i].clear();
        _users_hash_lock[i].unlock();
    }
}
///--------------PRIVATE------------------------------------------
void Storage::addUser(shared_ptr<User> user)
{
    uint32 uid = user->get("uid").toInt();
    uint32 hash = uid % USER_HASH_SIZE;
    _users_hash_lock[hash].lock();
    _users[hash][uid] = user;
    _users_hash_lock[hash].unlock();
}
shared_ptr<User> Storage::findUser(uint32 uid)
{
    uint32 hash = uid % USER_HASH_SIZE;
    _users_hash_lock[hash].lock();
    auto it_us = _users[hash].find ( uid );
    if ( it_us != _users[hash].end() )
    {
        _users_hash_lock[hash].unlock();
        return it_us->second;
    }
    else
    {
        _users_hash_lock[hash].unlock();
        return shared_ptr<User>();
    }
}
void Storage::removeUser(uint32 uid)
{
    uint32 hash = uid % USER_HASH_SIZE;
    _users_hash_lock[hash].lock();
    _users[hash].erase(uid);
    _users_hash_lock[hash].unlock();
}
///------------END PRIVATE------------------------------------------
int Storage::getLocalUsersCount()
{
    int count = 0;
    for (uint i = 0; i < USER_HASH_SIZE; ++i)
    {
        _users_hash_lock[i].lock();
        count += _users[i].size();
        _users_hash_lock[i].unlock();
    }
    return count;
}
shared_ptr<User> Storage::getLocalUser(long long int soc_id, int soc_net_id)
{
    Field *field;

    shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->query(DB_GET_UID_FROM__SOC_ID_SOC_NET_NAME, soc_id, soc_net_id));

    if (!qres.get())
        return createNewUser(soc_id, soc_net_id);

    field = qres->fetch();
    uint32 uid = field[0].getUInt32();
    return getLocalUser(uid);
}
shared_ptr<User> Storage::getLocalUser( uint32 uid)
{
    shared_ptr<User> user = findUser(uid);
    if (user == shared_ptr<User>())
        return loadUser(uid);
    else
        return user;
}
void Storage::addOnlineUser(SOCKET sock, shared_ptr<User> user)
{
    uint32 hash = sock % ONLINE_USER_HASH_SIZE;
    _online_users_hash_lock[hash].lock();
    _online_users[hash][sock] = user;
    _online_users_hash_lock[hash].unlock();
}
shared_ptr<User> Storage::getOnlineUser(SOCKET sock)
{
    uint32 hash = sock % ONLINE_USER_HASH_SIZE;
    _online_users_hash_lock[hash].lock();
    auto it_us = _online_users[hash].find ( sock );
    if ( it_us != _online_users[hash].end() )
    {
        _online_users_hash_lock[hash].unlock();
        return it_us->second;
    }
    else
    {
        _online_users_hash_lock[hash].unlock();
        return shared_ptr<User>();
    }
}
shared_ptr<UserExt> Storage::getExtUser( uint32 uid)
{
    return shared_ptr<UserExt>();
}
shared_ptr<UserInterface> Storage::getUser ( uint32 uid )
{
    Field *field;
    uint32 server_id;

    shared_ptr<UserInterface> user = getLocalUser(uid);
    if (user != shared_ptr<UserInterface>())
        return user;

    shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->query(DB_GET_ONLINE_USER__UID, uid));
    if (!qres.get())
        return shared_ptr<UserInterface>();

    field = qres->fetch();
    server_id = field[0].getUInt32();
    if (!server_id)
        return loadUser(uid);
    return shared_ptr<UserExt>(new UserExt(uid, server_id));
}
shared_ptr<User> Storage::loadUser(uint32 uid)
{
    Field *field;

    shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->query(DB_GET_USER_LOGIN__UID, uid));///fetch base user info from logins db
    if (!qres.get())
        return shared_ptr<User>();

    field = qres->fetch();

    int db_id 		= field[3].getUInt32();
    int online 		= field[4].getUInt32();
    if (online)
        return shared_ptr<User>();
    iDBManager->getSSDatabase()->execute(DB_SET_USER_SERVER_OWNER__SERVER_ID_UID, iServer->getId(), uid);///set server_id for online field(user server owner)
    shared_ptr<QueryResult> usr_qres(iDBManager->getDatabase(db_id)->query(DB_GET_USER_DATA__UID, uid));///fetch all user data
    if (!usr_qres.get())
        return shared_ptr<User>();

    field = usr_qres->fetch();
    shared_ptr<User> user(new User);

    for (uint32 i = 0; i < usr_qres->getFieldCount(); ++i)
    {
        switch (field[i].getType())
        {
        case MYSQL_TYPE_DECIMAL:
        case MYSQL_TYPE_TINY:
        case MYSQL_TYPE_SHORT:
        case MYSQL_TYPE_LONG:
        case MYSQL_TYPE_NULL:
        case MYSQL_TYPE_TIMESTAMP:
        case MYSQL_TYPE_LONGLONG:
        case MYSQL_TYPE_INT24:
            user->set(field[i].getFieldName(), field[i].getInt32());
            break;
        case MYSQL_TYPE_FLOAT:
        case MYSQL_TYPE_DOUBLE:
            user->set(field[i].getFieldName(), field[i].getFloat());
            break;
        case MYSQL_TYPE_DATE:
        case MYSQL_TYPE_TIME:
        case MYSQL_TYPE_DATETIME:
        case MYSQL_TYPE_YEAR:
        case MYSQL_TYPE_NEWDATE:
        case MYSQL_TYPE_VARCHAR:
        case MYSQL_TYPE_BIT:
        case MYSQL_TYPE_NEWDECIMAL:
        case MYSQL_TYPE_ENUM:
        case MYSQL_TYPE_SET:
        case MYSQL_TYPE_TINY_BLOB:
        case MYSQL_TYPE_MEDIUM_BLOB:
        case MYSQL_TYPE_LONG_BLOB:
        case MYSQL_TYPE_BLOB:
        case MYSQL_TYPE_VAR_STRING:
        case MYSQL_TYPE_STRING:
        case MYSQL_TYPE_GEOMETRY:
            user->set(field[i].getFieldName(), field[i].getString());
            break;
        default:
            break;
        }
    }
    addUser(user);
    return user;
}

shared_ptr<User> Storage::createNewUser(long long int soc_id, uint32 soc_net_id)
{
    uint32 db_id = iServer->getId();
    shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->queryNA(DB_GET_NEW_USER_FOR_UPDATE));
    if (!qres.get())
    {
        iDBManager->getSSDatabase()->waitExecuteNA(DB_PRE_CREATE_NEW_USERS);
        return createNewUser(soc_id, soc_net_id);
    }
    Field *fields = qres->fetch();
    uint32 new_uid = fields[0].getUInt32();

    iDBManager->getSSDatabase()->waitExecute(DB_UPDATE_LOCKED_FOR_UPDATE, soc_id, soc_net_id, db_id, db_id, new_uid);
    iDBManager->getDatabase(db_id)->waitExecute(DB_CREATE_USER_GAME_DB__UID, new_uid);

    return loadUser(new_uid);
}
