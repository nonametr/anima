#include "periodic_thread_caller.h"

initialiseSingleton ( PeriodicThreadCaller );

PeriodicThreadCaller::PeriodicThreadCaller()
{
    pthread_mutex_init( &_sleep_mutex, NULL );
    pthread_cond_init( &_sleep_cond, NULL );
    _runing.setVal(true);
    iThreadCore->startThread(this);
}
PeriodicThreadCaller::~PeriodicThreadCaller()
{
    for ( PeriodicThreadMap::iterator it_pt = _periodic_threads.begin(); it_pt != _periodic_threads.end(); ++it_pt)
    {
        for (uint32 i = 0; i < it_pt->second.threads_to_run.size(); ++i)
        {
            delete it_pt->second.threads_to_run[i];
        }
        it_pt->second.threads_to_run.clear();
    }
}
void PeriodicThreadCaller::run()
{
    struct timespec tv;
    struct timeval  tp;

    uint32 current_time;
    uint32 exam_time;
    uint32 sleeping_time;
    PeriodicThreadMap::iterator it_exam;
    while (true)
    {
        _pt_mutex.lock();
        if (!_runing.getVal())
        {
            _pt_mutex.unlock();
            break;
        }
        current_time = getTickCount();
        if (_periodic_threads.size())
        {
            it_exam = _periodic_threads.begin();
            exam_time = it_exam->first;
            if (exam_time <= current_time)
            {
                for (uint32 i = 0; i < it_exam->second.threads_to_run.size(); ++i)
                {
                    ThreadCore::getSingletonPtr()->startThreadNoDel(it_exam->second.threads_to_run[i]);
                    exam_time = current_time + it_exam->second.call_interval;///its next exam_time
                    _periodic_threads[exam_time] = it_exam->second;
                    sleeping_time = it_exam->second.call_interval;
                }
                _periodic_threads.erase(it_exam);
            }
            else
                sleeping_time = exam_time - current_time;
        }
        else
            sleeping_time = INFINITY_SLEEP_TIME;
        gettimeofday(&tp, NULL);
        tv.tv_sec = tp.tv_sec + sleeping_time;
        tv.tv_nsec = tp.tv_usec*1000;
        _pt_mutex.unlock();
        pthread_mutex_lock( &_sleep_mutex );
        pthread_cond_timedwait( &_sleep_cond, &_sleep_mutex, &tv );
        pthread_mutex_unlock( &_sleep_mutex );
    }
}
void PeriodicThreadCaller::onShutdown()
{
    _runing.setVal(false);
    pthread_cond_signal( &_sleep_cond );///waiking up periodic thread callback checks
}
void PeriodicThreadCaller::startPeriodicThread(Thread * thread, uint32 call_interval)
{
    uint32 exam_time = getTickCount() + call_interval;

    PeriodicThread period_th;
    period_th.call_interval = call_interval;
    period_th.threads_to_run.push_back(thread);
    _pt_mutex.lock();
    PeriodicThreadMap::iterator it_th = _periodic_threads.find(exam_time);
    if (it_th == _periodic_threads.end())
        _periodic_threads[exam_time] = period_th;
    else
        _periodic_threads[exam_time].threads_to_run.push_back(thread);
    _pt_mutex.unlock();
    pthread_cond_signal( &_sleep_cond );///waiking up periodic thread callback checks
}


