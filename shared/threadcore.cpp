#include "threadcore.h"
#include <unistd.h>

initialiseSingleton ( ThreadCore );

static void * thread_proc(void * param)
{
    ThreadController * t_control = (ThreadController*)param;
    tracelog(OPTIMAL, "Thread %u started.", t_control->GetId());

    while (true)
    {
        t_control->run();
        /// after resuming, this is where we will end up. start the loop again, check for tasks, then go back to the threadpool.
        t_control->suspend();
    }

    pthread_exit(0);
}

ThreadCore::ThreadCore()
{
    uint thread_count = _getNumCpus()*2;

    for (int i= 0; i < thread_count; ++i)
        initThread();

    tracelog(OPTIMAL, "Startup, launching %u precreated threads.", thread_count);
}

ThreadCore::~ThreadCore()
{

}
void ThreadCore::initThread()
{
    pthread_t target;
    ThreadController * t_control = new ThreadController(++_threadid_count);

    pthread_create(&target, NULL, &thread_proc, (void*)t_control);
    t_control->setup(target);
    pthread_detach(target);
}
int ThreadCore::_getNumCpus()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}
void ThreadCore::startThread(Thread * thread)
{
  
}
