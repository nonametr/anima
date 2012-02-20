#ifndef USER_H
#define USER_H

#include "user_interface.h"

class User : public UserInterface
{

public:
    User();
    virtual ~User();
    void onSessionClose(){};
};

#endif // USER_H
