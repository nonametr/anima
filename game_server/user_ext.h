#ifndef USER_EXT_H
#define USER_EXT_H

#include "user_interface.h"

///This class used to interact with users from other shards
class UserExt : public UserInterface
{

public:
    UserExt();
    virtual ~UserExt();
};

#endif // USER_EXT_H
