#ifndef USER_EXT_H
#define USER_EXT_H

#include "user_interface.h"

///This class used to interact with users from other shards
class UserExt : public UserInterface
{

public:
    UserExt(uint32 uid, uint32 server_id);
    virtual ~UserExt();
///--------------SETTERS----------------
    virtual void setUid(int v_uid);
    virtual void setSocialNet(int v_id);
    virtual void setSocialId(long int v_soc_id);
    virtual void setFirstName(string v_first_name);
    virtual void setLastName(string v_last_name);
    virtual void setNickName(string v_nick_name);
    virtual void setSex(int v_sex);
    virtual void setMusic(int v_music);
    virtual void setSound(int v_sound);
    virtual void setAdmin(int v_admin);
    virtual void setLastJoinUtime(int v_last_join);
    virtual void setRegistrationUtime(int v_reg_time);
    virtual void setLanguage(int v_lang);
    virtual void setInvitedFriendsCount(int v_inv_friends_count);
    virtual void setFriendsData(string v_friends_data);
    virtual void setAppFriendsData(string v_app_friends_data);
    virtual void setMoney(int v_money);
    virtual void setGold(int v_gold);
    virtual void setExp(int v_exp);
    virtual void setLvl(int v_lvl);
///-------------GETTERS-----------------
    virtual int getUid();
    virtual int getSocialNet();
    virtual long int getSocialId();
    virtual string getFirstName();
    virtual string getLastName();
    virtual string getNickName();
    virtual int getSex();
    virtual int getMusic();
    virtual int getSound();
    virtual int getAdmin();
    virtual int getLastJoinUtime();
    virtual int getRegistrationUtime();
    virtual int getLanguage();
    virtual int getInvitedFriendsCount();
    virtual string getFriendsData();
    virtual string getAppFriendsData();
    virtual int getMoney();
    virtual int getGold();
    virtual int getExp();
    virtual int getLvl();
private:
    uint32 _uid;
    uint32 _server_id;
};

#endif // USER_EXT_H
