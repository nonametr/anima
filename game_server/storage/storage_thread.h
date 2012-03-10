#ifndef STORAGE_THREAD_H
#define STORAGE_THREAD_H

#include "thread.h"
#include "common.h"
#include "storage.h"

#define UNLOAD_PERIOD 14400
class StorageThread : public Thread
{
public:
    StorageThread();
    virtual ~StorageThread();
    virtual void run();
    virtual void onShutdown(){};
};

#endif // STORAGE_THREAD_H
