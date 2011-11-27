#ifndef PERIODICTHREADCALLER_H
#define PERIODICTHREADCALLER_H

#include "singleton.h"
#include "thread.h"
#include <map>
#include "threadcore.h"

#define INFINITY_SLEEP_TIME 10000000

struct PeriodicThread
{
    std::vector<Thread*> threads_to_run;
    uint call_interval;
};

typedef std::map<uint, PeriodicThread> PeriodicThreadMap;

class PeriodicThreadCaller : public Thread, public Singleton<PeriodicThreadCaller>
{
public:
    PeriodicThreadCaller();
    virtual ~PeriodicThreadCaller();
    void run();
    void onShutdown();
    void startPeriodicThread(Thread * thread, uint call_interval);
private:
    PeriodicThreadMap _periodic_threads;///uint - time when need to resume thread

    bool _runing;
    Mutex _pt_mutex;
    pthread_cond_t _sleep_cond;
    pthread_mutex_t _sleep_mutex;
};

#define iPeriodicThreadCaller PeriodicThreadCaller::getSingletonPtr()
#endif // PERIODICTHREADCALLER_H

