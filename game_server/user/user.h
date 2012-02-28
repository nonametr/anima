#ifndef USER_H
#define USER_H

#include "user_interface.h"

class User : public UserInterface
{

public:
    User();
    virtual ~User();
    void onSessionClose() {};
///-------INTERFACE REALIZATION---------
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
///--------------SPECIAL----------------
///--------------SETTERS----------------
    void setLoadingTime(int utime);
///-------------GETTERS-----------------
    int getLoadingTime();
private:
    int _uid;
    int _social_net_id;
    long int _social_id;
    string _first_name;
    string _last_name;
    string _nick_name;
    int _sex;
    int _music;
    int _sound;
    int _admin;
    int _last_join_utime;
    int _reg_utime;
    int _language;
    int _inv_friends_count;
    string _friends_data;
    string _app_friends_data;
    int _money;
    int _gold;
    int _exp;
    int _lvl;
    int _loading_utime;
};

#endif // USER_H
