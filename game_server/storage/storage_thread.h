#ifndef STORAGE_THREAD_H
#define STORAGE_THREAD_H

#include "thread.h"
#include "common.h"
#include "storage.h"

class StorageThread : public Thread
{
public:
    StorageThread();
    virtual ~StorageThread();
    virtual void run();
    virtual void onShutdown(){};

private:
    uint _unload_period;
    uint _save_period;
};

#endif // STORAGE_THREAD_H
