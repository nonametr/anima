#ifndef THREADCORE_H
#define THREADCORE_H

#include <set>
#include "thread.h"
#include "common.h"
#include "config.h"
#include "thread_controller.h"

typedef std::set<ThreadController*> ThreadSet;

class ThreadCore : public Singleton<ThreadCore>
{
public:
    ThreadCore();
    virtual ~ThreadCore();

    /// tries to use precreated thread, if not found free one than creates a new thread
    ThreadController *startThread(Thread * thread);
    void startThreadNoDel(Thread * thread);
    bool threadExit(ThreadController * t_control);
    void shutdown();
private:
    void initThread();
    int _getNumCpus();

    AtomicCounter _threadid_count;
    int _numCPU;
    ThreadSet _free_threads;
    ThreadSet _active_threads;
    Mutex _mutex;
};

#define iThreadCore ThreadCore::getSingletonPtr()

#endif // THREADCORE_H
