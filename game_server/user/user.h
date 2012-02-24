#ifndef USER_H
#define USER_H

#include "user_interface.h"

class User : public UserInterface
{

public:
    User();
    virtual ~User();
    void onSessionClose() {};
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
private:
    int _money;
    int _gold;
    int _exp;
    int _lvl;
};

#endif // USER_H
