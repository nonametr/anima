#include "storage.h"
#include "singleton.h"
#include "game_server.h"
#include "sql_define.h"
#include "ext_server_manager.h"
#include <time.h>

initialiseSingleton ( Storage );

Storage::Storage()
{

}
Storage::~Storage()
{

}
shared_ptr<User> Storage::getLocalUser( uint32 uid)
{
    auto it_us = _users.find ( uid );
    if ( it_us != _users.end() )
        return it_us->second;
    return shared_ptr<User>();
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
    iDBManager->getSSDatabase()->execute(DB_SET_USER_SERVER_OWNER__SERVER_ID, iServer->getId());///set server_id for online field(user server owner)
    shared_ptr<QueryResult> usr_qres(iDBManager->getDatabase(db_id)->query(DB_GET_USER_DATA__UID, uid));///fetch all user data
    if (!usr_qres.get())
        return shared_ptr<User>();

    field = usr_qres->fetch();

    User *user = new User;
    user->setUid(field[0].getUInt32());
    user->setSocialId(field[1].getUInt64());
    user->setSocialNet(field[2].getUInt32());
    user->setFirstName(field[3].getString());
    user->setLastName(field[4].getString());
    user->setNickName(field[5].getString());
    user->setSex(field[6].getUInt32());
    user->setMoney(field[7].getUInt32());
    user->setGold(field[8].getUInt32());
    user->setExp(field[9].getUInt32());
    user->setLvl(field[10].getUInt32());
    user->setMusic(field[11].getUInt32());
    user->setSound(field[12].getUInt32());
    user->setAdmin(field[13].getUInt32());
    user->setLastJoinUtime(field[14].getUInt32());
    user->setRegistrationUtime(field[15].getUInt32());
    user->setLanguage(field[16].getUInt32());
    user->setInvitedFriendsCount(field[17].getUInt32());
    user->setFriendsData(field[18].getString());
    user->setAppFriendsData(field[19].getString());
    user->setLoadingTime(time(NULL));

    return shared_ptr<User>(user);
}

shared_ptr<User> Storage::createNewUser(long int soc_id, uint32 soc_net_id)
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
    iDBManager->getSSDatabase()->execute(DB_UPDATE_LOCKED_FOR_UPDATE, soc_id, soc_net_id, db_id, iServer->getId());
//     iDBManager->getDatabase(db_id)->execute(DB_CREATE_USER_GAME_DB__UID, new_uid);
}