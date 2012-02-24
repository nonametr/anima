#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "../../shared/common.h"

class UserInterface
{

public:
    UserInterface(){};
    virtual ~UserInterface(){};
///--------------SETTERS----------------
    virtual void setMoney(int v_money) = 0;
    virtual void setGold(int v_gold) = 0;
    virtual void setExp(int v_exp) = 0;
    virtual void setLvl(int v_lvl) = 0;
///-------------GETTERS-----------------
    virtual int getMoney() = 0;
    virtual int getGold() = 0;
    virtual int getExp() = 0;
    virtual int getLvl() = 0;
};

#endif // USER_INTERFACE_H
