#ifndef LOCATION_H
#define LOCATION_H

#include "common.h"

class location
{

public:
    location();
    virtual ~location();
private:
    uint id;
    uint start_time;
    uint limit_end_time;
    uint lose_counter;
    uint win_counter;    
};

#endif // LOCATION_H
