#ifndef THREAD_CONTROLLER_H
#define THREAD_CONTROLLER_H

class ThreadController
{
public:
    void setup(pthread_t h)
    {
        _target = NULL;
        _handle = h;
        pthread_mutex_init(&_mutex,NULL);
        pthread_cond_init(&_cond,NULL);
    }
    explicit ThreadController(uint thread_id)
    {
        _thread_id = thread_id;
    }
    ~ThreadController()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }
    void suspend()
    {
        if (_target)
        {
            delete _target;
            _target = NULL;
        }
        pthread_cond_wait(&_cond, &_mutex);
    }
    void resume()
    {
        pthread_cond_signal(&_cond);
    }
    void run()
    {
        if (_target)
            _target->run();;
    }
    void join()
    {
        pthread_join(_handle,NULL);
    }
    inline uint GetId() {
        return (uint)_thread_id;
    }
private:
    pthread_cond_t _cond;
    pthread_mutex_t _mutex;
    int _thread_id;
    pthread_t _handle;
    Thread *_target;
};

#endif // THREAD_CONTROLLER_H