#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "common.h"

class UserInterface
{

public:
    UserInterface(){};
    virtual ~UserInterface(){};
///--------------SETTERS----------------
    virtual void setUid(int v_uid) = 0;
    virtual void setSocialNet(int v_id) = 0;
    virtual void setSocialId(long int v_soc_id) = 0;
    virtual void setFirstName(string v_first_name) = 0;
    virtual void setLastName(string v_last_name) = 0;
    virtual void setNickName(string v_nick_name) = 0;
    virtual void setSex(int v_sex) = 0;
    virtual void setMusic(int v_music) = 0;
    virtual void setSound(int v_sound) = 0;
    virtual void setAdmin(int v_admin) = 0;
    virtual void setLastJoinUtime(int v_last_join) = 0;
    virtual void setRegistrationUtime(int v_reg_time) = 0;
    virtual void setLanguage(int v_lang) = 0;
    virtual void setInvitedFriendsCount(int v_inv_friends_count) = 0;
    virtual void setFriendsData(string v_friends_data) = 0;
    virtual void setAppFriendsData(string v_app_friends_data) = 0;
    
    virtual void setMoney(int v_money) = 0;
    virtual void setGold(int v_gold) = 0;
    virtual void setExp(int v_exp) = 0;
    virtual void setLvl(int v_lvl) = 0;
///-------------GETTERS-----------------
    virtual int getUid() = 0;
    virtual int getSocialNet() = 0;
    virtual long int getSocialId() = 0;
    virtual string getFirstName() = 0;
    virtual string getLastName() = 0;
    virtual string getNickName() = 0;
    virtual int getSex() = 0;
    virtual int getMusic() = 0;
    virtual int getSound() = 0;
    virtual int getAdmin() = 0;
    virtual int getLastJoinUtime() = 0;
    virtual int getRegistrationUtime() = 0;
    virtual int getLanguage() = 0;
    virtual int getInvitedFriendsCount() = 0;
    virtual string getFriendsData() = 0;
    virtual string getAppFriendsData() = 0;
    virtual int getMoney() = 0;
    virtual int getGold() = 0;
    virtual int getExp() = 0;
    virtual int getLvl() = 0;
};

#endif // USER_INTERFACE_H
