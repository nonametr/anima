#include "periodicthreadcaller.h"

initialiseSingleton ( PeriodicThreadCaller );

PeriodicThreadCaller::PeriodicThreadCaller()
{
    ThreadCore::getSingletonPtr()->startThread(this);
}

PeriodicThreadCaller::~PeriodicThreadCaller()
{

}
void PeriodicThreadCaller::run()
{
    pthread_mutex_init( &_sleep_mutex, NULL );
    pthread_cond_init( &_sleep_cond, NULL );

    struct timespec tv;
    uint current_time;
    uint exam_time;
    PeriodicThreadMap::iterator it_exam;
    while (true)
    {
        current_time = getTickCount();
        _pt_mutex.lock();
        it_exam = _periodic_threads.begin();
        exam_time = it_exam->first;
        if (exam_time <= current_time)
        {
            for (uint i = 0; i < it_exam->second.threads_to_run.size(); ++i)
            {
                ThreadCore::getSingletonPtr()->startThread(it_exam->second.threads_to_run[i]);
                exam_time = current_time + it_exam->second.call_interval;
                _periodic_threads[exam_time] = it_exam->second;
                _periodic_threads.erase(it_exam);
            }
        }
        tv.tv_nsec = 0;
        tv.tv_sec = _periodic_threads.begin()->first;
        _pt_mutex.unlock();
        pthread_mutex_lock( &_sleep_mutex );
        pthread_cond_timedwait( &_sleep_cond, &_sleep_mutex, &tv );
        pthread_mutex_unlock( &_sleep_mutex );
    }
}
void PeriodicThreadCaller::startPeriodicThread(Thread * thread, uint call_interval)
{
    uint exam_time = getTickCount() + call_interval;

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

