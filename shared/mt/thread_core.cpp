#include "thread_core.h"
#include <unistd.h>

initialiseSingleton ( ThreadCore );

static void * thread_proc(void * param)
{
    ThreadController * t_control = (ThreadController*)param;
    tracelog(OPTIMAL, "Thread %u started.", t_control->getId());

    while (true)
    {
        if (t_control->getTarget())
        {
            t_control->run();
        }
        ///after resuming, this is where we will end up. start the loop again, check for tasks, then go back to wait
        if (iThreadCore->threadExit(t_control))
            break;
        t_control->suspend();
    }

    pthread_exit(0);
}
bool ThreadCore::threadExit(ThreadController * t_control)
{
    _mutex.lock();
    /// we're definitely no longer active
    _active_threads.erase(t_control);

    if (!t_control->isRuning())
    {
        _free_threads.erase(t_control);
        delete t_control;
        _mutex.unlock();
        return true;
    }

    /// enter the "suspended" pool
    _free_threads.insert(t_control);

//     tracelog(4,"Thread %u entered suspend state.", t_control->getId());
    _mutex.unlock();
    return false;
}
ThreadCore::ThreadCore() : shutting_down(false)
{
    uint32 thread_count = _getNumCpus()*8;

    for (uint32 i= 0; i < thread_count; ++i)
        initThread();

    tracelog(OPTIMAL, "Startup, launching %u precreated threads.", thread_count);
}

ThreadCore::~ThreadCore()
{
    shutdown();
}
void ThreadCore::initThread()
{
    pthread_t target;
    ThreadController * t_control = new ThreadController(++_threadid_count);

    pthread_create(&target, NULL, &thread_proc, (void*)t_control);
    t_control->setup(target);
    pthread_detach(target);

    _mutex.lock();
    _free_threads.insert(t_control);
    _mutex.unlock();
}
int ThreadCore::_getNumCpus()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}
void ThreadCore::startThreadNoDel(Thread * thread)
{
    ASSERT(thread != NULL);
    if (!_mutex.try_1k_lock())
        return;
    ThreadController * t_control = startThread(thread);
    t_control->setDeleteOnExit(false);
    _mutex.unlock();
}
ThreadController * ThreadCore::startThread(Thread * thread)
{
    ASSERT(thread != NULL);
    ThreadController * t_control;
    _mutex.lock();
    /// grab one from the pool, if we have any
    if (_free_threads.size())
    {
        t_control = *_free_threads.begin();
        _free_threads.erase(_free_threads.begin());
        _active_threads.insert(t_control);

        /// execute the task on this thread
        t_control->setExecutionTarget(thread);
	thread->setTid(t_control->getId());

        /// resume the thread, and it should start working
        t_control->resume();
//         tracelog(4, "Precreated thread %u now in use", t_control->getId());
    }
    else
    {
        /// creating a aditional new thread
        initThread();
        t_control = startThread(thread);
    }
    _mutex.unlock();
    return t_control;
}
void ThreadCore::shutdown()
{
    shutting_down = true;
    _mutex.lock();
    for ( ThreadSet::iterator itr = _free_threads.begin(); itr != _free_threads.end(); ++itr)
    {
        ThreadController *t_control = *itr;
        t_control->stop();
    }
    for ( ThreadSet::iterator itr = _active_threads.begin(); itr != _active_threads.end(); ++itr)
    {
        ThreadController *t_control = *itr;
        t_control->onShutdown();
    }
    _mutex.unlock();
    for (int i = 0;; i++)
    {
        _mutex.lock();
        /**if we are here then a thread in the free pool checked if it was being shut down just before shutdown() was called,
        			but called suspend() just after killing free threads. All we need to do is to resume it.*/
        if (_active_threads.size() || _free_threads.size())
        {
            if ( i != 0 && _free_threads.size() != 0 )
            {
                ThreadController * t_control;
                ThreadSet::iterator itr;
                for (itr = _free_threads.begin(); itr != _free_threads.end(); ++itr)
                {
                    t_control = *itr;
                    t_control->stop();
                }
            }
            tracelog(4, "Stoping threads... %u active and %u free threads remaining...", static_cast<uint32>(_active_threads.size()),
                     static_cast<uint32>(_free_threads.size()) );
            _mutex.unlock();
            sleep(1);
            continue;
        }
        _mutex.unlock();
        break;
    }
}

