#include "storage_thread.h"

StorageThread::StorageThread()
{

}

StorageThread::~StorageThread()
{

}

void StorageThread::run()
{
    for (uint32 i = 0; i < USER_HASH_SIZE; ++i)
    {
        iStorage->_users_hash_lock[i].lock();
        for (auto it = iStorage->_users[i].begin(); it != iStorage->_users[i].end(); ++it)
        {
            if ( (iStorage->getCurrentTime() - it->second->getLastActivity()) > UNLOAD_PERIOD )
            {
                iStorage->removeUser(it->first);
            }
        }
        iStorage->_users_hash_lock[i].unlock();
    }
}

