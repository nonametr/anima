#include "user.h"

User::User()
{

}
User::~User()
{

}
///--------------SETTERS----------------
void User::setUid(int v_uid)
{
    _uid = v_uid;
}
void User::setSocialNet(int v_id)
{
    _social_net_id = v_id;
}
void User::setSocialId(long int v_soc_id)
{
    _social_id = v_soc_id;
}
void User::setFirstName(string v_first_name)
{
    _first_name = v_first_name;
}
void User::setLastName(string v_last_name)
{
    _last_name = v_last_name;
}
void User::setNickName(string v_nick_name)
{
    _nick_name = v_nick_name;
}
void User::setSex(int v_sex)
{
    _sex = v_sex;
}
void User::setMusic(int v_music)
{
    _music = v_music;
}
void User::setSound(int v_sound)
{
    _sound = v_sound;
}
void User::setAdmin(int v_admin)
{
    _admin = v_admin;
}
void User::setLastJoinUtime(int v_last_join)
{
    _last_join_utime = v_last_join;
}
void User::setRegistrationUtime(int v_reg_time)
{
    _reg_utime = v_reg_time;
}
void User::setLanguage(int v_lang)
{
    _language = v_lang;
}
void User::setInvitedFriendsCount(int v_inv_friends_count)
{
    _inv_friends_count = v_inv_friends_count;
}
void User::setFriendsData(string v_friends_data)
{
    _friends_data = v_friends_data;
}
void User::setAppFriendsData(string v_app_friends_data)
{
    _app_friends_data = v_app_friends_data;
}
void User::setMoney(int v_money)
{
    _money = v_money;
}
void User::setGold(int v_gold)
{
    _gold = v_gold;
}
void User::setExp(int v_exp)
{
    _exp = v_exp;
}
void User::setLvl(int v_lvl)
{
    _lvl = v_lvl;
}
///-------------GETTERS-----------------
int User::getMoney()
{
    return _money;
}
int User::getGold()
{
    return _gold;
}
int User::getExp()
{
    return _exp;
}
int User::getLvl()
{
    return _lvl;
}
int User::getUid()
{
    return _uid;
}
int User::getSocialNet()
{
    return _social_net_id;
}
long int User::getSocialId()
{
    return _social_id;
}
string User::getFirstName()
{
    return _first_name;
}
string User::getLastName()
{
    return _last_name;
}
string User::getNickName()
{
    return _nick_name;
}
int User::getSex()
{
    return _sex;
}
int User::getMusic()
{
    return _music;
}
int User::getSound()
{
    return _sound;
}
int User::getAdmin()
{
    return _admin;
}
int User::getLastJoinUtime()
{
    return _last_join_utime;
}
int User::getRegistrationUtime()
{
    return _reg_utime;
}
int User::getLanguage()
{
    return _language;
}
int User::getInvitedFriendsCount()
{
    return _inv_friends_count;
}
string User::getFriendsData()
{
    return _friends_data;
}
string User::getAppFriendsData()
{
    return _app_friends_data;
}
///--------------SPECIAL----------------
///--------------SETTERS----------------
void User::setLoadingTime(int utime)
{
}
///-------------GETTERS-----------------
int User::getLoadingTime()
{
    return 0;
}
