#ifndef USER_EXT_H
#define USER_EXT_H

#include "user_interface.h"

///This class used to interact with users from other shards
class UserExt : public UserInterface
{

public:
    UserExt(uint32 uid);
    virtual ~UserExt();
    ///--------------SETTERS----------------
    virtual void setMoney(int v_money);
    virtual void setGold(int v_gold);
    virtual void setExp(int v_exp);
    virtual void setLvl(int v_lvl);
///-------------GETTERS-----------------
    virtual int getMoney();
    virtual int getGold();
    virtual int getExp();
    virtual int getLvl();
};

#endif // USER_EXT_H
