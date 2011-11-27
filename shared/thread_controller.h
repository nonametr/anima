#ifndef THREAD_CONTROLLER_H
#define THREAD_CONTROLLER_H

class ThreadController
{
public:
    explicit ThreadController(uint thread_id)
    {
        _runing = true;
        _delete_target_on_exit = true;
        _target_thread = NULL;
        _thread_id = thread_id;
	pthread_mutex_init(&_mutex,NULL);
        pthread_cond_init(&_cond,NULL);
    }
    ~ThreadController()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }
    void setDeleteOnExit(bool delete_on_exit)
    {
        _delete_target_on_exit = delete_on_exit;
    }
    void setup(pthread_t h)
    {
        _handle = h;
    }
    void setExecutionTarget(Thread *target)
    {
        _target_thread = target;
    }
    void suspend()
    {
        if (_target_thread && _delete_target_on_exit)
        {
            delete _target_thread;
            _target_thread = NULL;
        }
        else
            _delete_target_on_exit = true;
        pthread_cond_wait(&_cond, &_mutex);
    }
    void resume()
    {
        pthread_cond_signal(&_cond);
    }
    void run()
    {
        _target_thread->run();
    }
    void stop()
    {
        _runing = false;
        _target_thread = NULL;
        resume();
    }
    void onShutdown()
    {
        _target_thread->onShutdown();
    }
    Thread * getTarget()
    {
        return _target_thread;
    }
    bool isRuning()
    {
        return _runing;
    }
    void join()
    {
        pthread_join(_handle,NULL);
    }
    inline uint GetId()
    {
        return (uint)_thread_id;
    }
private:
    pthread_cond_t _cond;
    pthread_mutex_t _mutex;
    pthread_t _handle;
    int _thread_id;
    
    bool _runing;
    bool _delete_target_on_exit;
    Thread *_target_thread;
};

#endif // THREAD_CONTROLLER_H
