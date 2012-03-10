#ifndef STORAGE_TIMER_H
#define STORAGE_TIMER_H

#include "thread.h"
#include "storage.h"
#include <time.h>

#define TIME_UPDATE_PERIOD 10

class StorageTimer : public Thread
{
public:
    StorageTimer();
    virtual ~StorageTimer();
    virtual void run();
    virtual void onShutdown(){};
};

#endif // STORAGE_TIMER_H
