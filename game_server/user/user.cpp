#include "user.h"

User::User()
{

}

User::~User()
{

}

///--------------SETTERS----------------
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

