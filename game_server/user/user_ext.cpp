#include "user_ext.h"
#include "command_structs.h"
#include "ext_server_manager.h"

UserExt::UserExt(uint32 uid, uint32 server_id) : _uid(uid), _server_id(server_id)
{

}
UserExt::~UserExt()
{

}
///--------------SETTERS----------------
void UserExt::setMoney(int v_money)
{
    Packet pkt = C1Int::create(_uid, v_money);

    ExtServerConnection *connection = iExtServerManager->getById(_server_id);
    if (connection == NULL)
    {
        return;
    }

    connection->sendPacket(&pkt);
}
void UserExt::setGold(int v_gold)
{
}
void UserExt::setExp(int v_exp)
{
}
void UserExt::setLvl(int v_lvl)
{
}
void UserExt::setUid(int v_uid)
{
}
void UserExt::setSocialNet(int v_id)
{
}
void UserExt::setSocialId(long int v_soc_id)
{
}
void UserExt::setFirstName(string v_first_name)
{
}
void UserExt::setLastName(string v_last_name)
{

}
void UserExt::setNickName(string v_nick_name)
{

}
void UserExt::setSex(int v_sex)
{

}
void UserExt::setMusic(int v_music)
{

}
void UserExt::setSound(int v_sound)
{

}
void UserExt::setAdmin(int v_admin)
{

}
void UserExt::setLastJoinUtime(int v_last_join)
{

}
void UserExt::setRegistrationUtime(int v_reg_time)
{

}
void UserExt::setLanguage(int v_lang)
{

}
void UserExt::setInvitedFriendsCount(int v_inv_friends_count)
{

}
void UserExt::setFriendsData(string v_friends_data)
{

}
void UserExt::setAppFriendsData(string v_app_friends_data)
{

}
///-------------GETTERS-----------------
int UserExt::getMoney()
{
    return 0;
}
int UserExt::getGold()
{
    return 0;
}
int UserExt::getExp()
{
    return 0;
}
int UserExt::getLvl()
{
    return 0;
}
int UserExt::getUid()
{
    return 0;
}
int UserExt::getSocialNet()
{
    return 0;
}
long int UserExt::getSocialId()
{
    return 0;
}
string UserExt::getFirstName()
{
    return "";
}
string UserExt::getLastName()
{
    return "";
}
string UserExt::getNickName()
{
    return "";
}
int UserExt::getSex()
{
    return 0;
}
int UserExt::getMusic()
{
    return 0;
}
int UserExt::getSound()
{
    return 0;
}
int UserExt::getAdmin()
{
    return 0;
}
int UserExt::getLastJoinUtime()
{
    return 0;
}
int UserExt::getRegistrationUtime()
{
    return 0;
}
int UserExt::getLanguage()
{
    return 0;
}
int UserExt::getInvitedFriendsCount()
{
    return 0;
}
string UserExt::getFriendsData()
{
    return "";
}
string UserExt::getAppFriendsData()
{
    return "";
}

