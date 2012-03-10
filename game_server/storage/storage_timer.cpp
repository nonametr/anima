#include "storage_timer.h"

StorageTimer::StorageTimer()
{

}

StorageTimer::~StorageTimer()
{

}
void StorageTimer::run()
{
    iStorage->_time = time(NULL);
}

