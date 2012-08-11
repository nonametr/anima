#ifndef EXEPTION_H
#define EXEPTION_H

#include "common.h"
#include <string>

class Packet;
using namespace std;

namespace MSG
{
enum MESSAGES
{
    JOIN = 2000,
    LOCATION_START = 2001,
    LOCATION_WIN = 2002,
    LOCATION_LOSE = 2003,
    BOSS_ON_COOLDOWN = 2004,
    EXCHANGE_SUCCESS = 2005,
    REQ_COLL_FAIL = 2006,
    REQ_COLL_SUCCESS = 2007,
    BOSS_NOT_IN_FIGHT = 2008,
    BOSS_IN_FIGHT = 2009,
    BOSS_WIN_REWARD = 2010,
    BOSS_LOSE_REWARD = 2011
};
};

class ErrorExeption
{
public:
    enum ErrorExeptionCode
    {
        ID_NOT_FOUND_IN_DICT = 1,
        ID_NOT_FOUND_IN_OBJECT_LIST = 2,
        USER_NOT_FOUND = 3,
        WRONG_PACKET_DATA = 4,
        VALUE_NOT_FOUND = 5,
        OBJECT_NOT_FOUND = 6,
        PRIVATE_OBJECT_NOT_FOUND = 7,
        NAME_NOT_FOUND_IN_DICT = 8,
        VALUE_NOT_FOUND_IN_OBJECT = 9,
        DESERIALIZATION_ERROR = 10,
        USER_LOAD_ERROR = 11,


        UNLOCK_CONDITION_FAIL = 1000,
        LOCATION_ALLREADY_IN_WORK = 1001,
        LOCATION_CANT_FINISH = 1002,
        LOCATION_LOSE = 1003,
        OTHER_BOSS_FIGHT_IN_PROGRESS = 1004,
        BOSS_STRIKE_NO_ITEM = 1005,
	NOT_ENOUGHT_ITEMS = 1006
    };
    ErrorExeption( ErrorExeptionCode code, string line ) : err_code ( code )
    {
        this->_line = line;
        throw *this;
    };
    void emitError ( Packet *pkt, uint err_msg_id );

    void doCatch ( Packet *pkt );

private:
    ErrorExeptionCode err_code;
    string _line;
};

#endif
