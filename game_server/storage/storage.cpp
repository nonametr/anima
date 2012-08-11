#include "storage.h"
#include "singleton.h"
#include "game_server.h"
#include "sql_define.h"
#include "ext_server_manager.h"
#include <time.h>
#include <mysql/mysql.h>

initialiseSingleton ( Storage );

int Storage::_time = time(NULL);

Storage::Storage()
{
      iPeriodicThreadCaller->startPeriodicThread(new StorageThread, 9);
      iPeriodicThreadCaller->startPeriodicThread(new StorageTimer, TIME_UPDATE_PERIOD);
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
void Storage::addUser(User* user)
{
    uint32 uid = user->get("uid")->getInt();
    uint32 hash = uid % USER_HASH_SIZE;
    _users_hash_lock[hash].lock();
    _users[hash][uid] = user;
    _users_hash_lock[hash].unlock();
}
User* Storage::findUser(uint32 uid)
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
        return NULL;
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
User* Storage::loadLocalUser(SOCKET sock, long long int soc_id, int soc_net_id)
{
    User* usr = getLocalUser(soc_id, soc_net_id);
    if (usr == NULL)
         ErrorExeption(ErrorExeption::USER_NOT_FOUND, intToString(__LINE__)+string(" ")+ string(__FUNCTION__));
    addOnlineUser(sock, usr);
    return usr;
}
User* Storage::getLocalUser(long long int soc_id, int soc_net_id)
{
    Field *field;

    shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->query(DB_GET_UID_FROM__SOC_ID_SOC_NET_NAME, soc_id, soc_net_id));

    if (!qres.get())
        return getNewUser(soc_id, soc_net_id);

    field = qres->fetch();
    uint32 uid = field[0].getUInt32();
    return getLocalUser(uid);
}
User* Storage::getLocalUser( uint32 uid)
{
    User* user = findUser(uid);
    if (user == NULL)
        return loadUser(uid);
    else
        return user;
}
void Storage::addOnlineUser(SOCKET sock, User* user)
{
    uint32 hash = sock % ONLINE_USER_HASH_SIZE;
    _online_users_hash_lock[hash].lock();
    _online_users[hash][sock] = user;
    _online_users_hash_lock[hash].unlock();
}
User* Storage::getOnlineUser(SOCKET sock)
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
        return NULL;
    }
}
// shared_ptr<UserExt> Storage::getExtUser( uint32 uid)
// {
//     return shared_ptr<UserExt>();
// }
// shared_ptr<UserInterface> Storage::getUser ( uint32 uid )
// {
//     Field *field;
//     uint32 server_id;
//
//     shared_ptr<UserInterface> user = getLocalUser(uid);
//     if (user != shared_ptr<UserInterface>())
//         return user;
//
//     shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->query(DB_GET_ONLINE_USER__UID, uid));
//     if (!qres.get())
//         return shared_ptr<UserInterface>();
//
//     field = qres->fetch();
//     server_id = field[0].getUInt32();
//     if (!server_id)
//         return loadUser(uid);
//     return shared_ptr<UserExt>(new UserExt(uid, server_id));
// }
void Storage::loadUserObjects(User* usr, shared_ptr<QueryResult> usr_qres)
{
    Field *field;
    field = usr_qres->fetch();

    for (uint32 i = 0; i < usr_qres->getFieldCount(); ++i)
    {
        switch (field[i].getType())
        {
        case MYSQL_TYPE_DATE:
        case MYSQL_TYPE_TIME:
        case MYSQL_TYPE_DATETIME:
        case MYSQL_TYPE_YEAR:
        case MYSQL_TYPE_NEWDATE:
        case MYSQL_TYPE_VARCHAR:
        case MYSQL_TYPE_ENUM:
        case MYSQL_TYPE_SET:
        case MYSQL_TYPE_TINY_BLOB:
        case MYSQL_TYPE_MEDIUM_BLOB:
        case MYSQL_TYPE_LONG_BLOB:
        case MYSQL_TYPE_BLOB:
        case MYSQL_TYPE_VAR_STRING:
        case MYSQL_TYPE_STRING:
            usr->setObjectList(field[i].getFieldName(), field[i].getString());
            break;
        default:
            break;
        }
    }
}
void Storage::loadUserPrivateObjects(User* usr, shared_ptr<QueryResult> usr_qres)
{
    Field *field;
    field = usr_qres->fetch();

    for (uint32 i = 0; i < usr_qres->getFieldCount(); ++i)
    {
        switch (field[i].getType())
        {
        case MYSQL_TYPE_DATE:
        case MYSQL_TYPE_TIME:
        case MYSQL_TYPE_DATETIME:
        case MYSQL_TYPE_YEAR:
        case MYSQL_TYPE_NEWDATE:
        case MYSQL_TYPE_VARCHAR:
        case MYSQL_TYPE_ENUM:
        case MYSQL_TYPE_SET:
        case MYSQL_TYPE_TINY_BLOB:
        case MYSQL_TYPE_MEDIUM_BLOB:
        case MYSQL_TYPE_LONG_BLOB:
        case MYSQL_TYPE_BLOB:
        case MYSQL_TYPE_VAR_STRING:
        case MYSQL_TYPE_STRING:
            usr->setPrivateObjectList(field[i].getFieldName(), field[i].getString());
            break;
        default:
            break;
        }
    }
}
void Storage::loadUserData(User* usr, shared_ptr<QueryResult> usr_qres)
{
    Field *field;
    field = usr_qres->fetch();

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
            usr->set(field[i].getFieldName(), field[i].getInt32());
            break;
        case MYSQL_TYPE_FLOAT:
        case MYSQL_TYPE_DOUBLE:
            usr->set(field[i].getFieldName(), field[i].getFloat());
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
            usr->set(field[i].getFieldName(), field[i].getString());
            break;
        default:
            break;
        }
    }
}
User* Storage::loadUser(uint32 uid)
{
    Field *field;
    shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->query(DB_GET_USER_LOGIN__UID, uid));///fetch base user info from logins db
    if (!qres.get())
        return NULL;
    field = qres->fetch();

    int db_id 		= field[3].getUInt32();
    int online 		= field[4].getUInt32();
    if (online || db_id == 0)
        return NULL;
    iDBManager->getSSDatabase()->execute(DB_SET_USER_SERVER_OWNER__SERVER_ID_UID, iServer->getId(), uid);///set server_id for online field(user server owner)
    shared_ptr<QueryResult> usr_data(iDBManager->getDatabase(db_id)->query(DB_GET_USER_DATA__UID, uid));///fetch all user data
    shared_ptr<QueryResult> usr_objects(iDBManager->getDatabase(db_id)->query(DB_GET_USER_DATA_OBJECTS__UID,  uid));///fetch all user objects
    shared_ptr<QueryResult> usr_private_objects(iDBManager->getDatabase(db_id)->query(DB_GET_USER_DATA_PRIVATE__UID,  uid));///fetch all user private objects
    if (!usr_data.get() && !usr_objects.get() && !usr_private_objects.get())
         ErrorExeption(ErrorExeption::USER_LOAD_ERROR, intToString(__LINE__)+string(" ")+ string(__FUNCTION__));

    User* user = new User;

    loadUserData(user, usr_data);
    loadUserObjects(user, usr_objects);
    loadUserPrivateObjects(user, usr_private_objects);

    addUser(user);
    return user;
}

uint32 Storage::createUserLogin(long long int soc_id, uint32 soc_net_id)
{
    uint32 new_uid;
    uint32 db_id = iServer->getId();
    shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->queryNA(DB_GET_NEW_USER_FOR_UPDATE));
    if (!qres.get())
    {
        iDBManager->getSSDatabase()->waitExecuteNA(DB_PRE_CREATE_NEW_USERS);
        return createUserLogin(soc_id, soc_net_id);
    }
    else
    {
        Field *fields = qres->fetch();
        new_uid = fields[0].getUInt32();

        iDBManager->getSSDatabase()->waitExecute(DB_UPDATE_LOCKED_FOR_UPDATE, soc_id, soc_net_id, db_id, new_uid);
        return new_uid;
    }
}
void Storage::createUserData(long long int soc_id, uint32 soc_net_id, uint32 uid)
{
    uint32 db_id = iServer->getId();
    shared_ptr<QueryResult> qres_data(iDBManager->getDatabase(db_id)->queryNA(DB_USER_DATA_GET_NEW_USER_FOR_UPDATE));
    if (!qres_data.get())
    {
        iDBManager->getDatabase(db_id)->waitExecuteNA(DB_USER_DATA_PRE_CREATE_NEW_USERS);
        return createUserData(soc_id, soc_net_id, uid);
    }
    else
    {
        shared_ptr<QueryResult> qres_objects(iDBManager->getDatabase(db_id)->queryNA(DB_USER_OBJECT_GET_NEW_USER_FOR_UPDATE));
        shared_ptr<QueryResult> qres_private(iDBManager->getDatabase(db_id)->queryNA(DB_USER_PRIVATE_GET_NEW_USER_FOR_UPDATE));
        Field *fields_data 	= qres_data->fetch();
        Field *fields_objects 	= qres_objects->fetch();
        Field *fields_private 	= qres_private->fetch();
        uint old_data 		= fields_data[0].getUInt32();
        uint old_objects 	= fields_objects[0].getUInt32();
        uint old_private 	= fields_private[0].getUInt32();
        iDBManager->getDatabase(db_id)->waitExecute(DB_USER_DATA_UPDATE_LOCKED_FOR_UPDATE__NEWUID_OLDUID, uid, old_data);
        iDBManager->getDatabase(db_id)->waitExecute(DB_USER_OBJECT_UPDATE_LOCKED_FOR_UPDATE__NEWUID_OLDUID, uid, old_objects);
        iDBManager->getDatabase(db_id)->waitExecute(DB_USER_PRIVATE_UPDATE_LOCKED_FOR_UPDATE__NEWUID_OLDUID, uid, old_private);
    }
}
User* Storage::getNewUser(long long int soc_id, uint32 soc_net_id)
{
    uint32 new_uid = createUserLogin(soc_id, soc_net_id);
    createUserData(soc_id, soc_net_id, new_uid);

    User *new_usr = iDictManager->cloneTemplateUser();
    new_usr->set("uid", new_uid);
    new_usr->set("social_id", soc_id);
    new_usr->set("social_net_id", 0);
    addUser(new_usr);
    return new_usr;
}

