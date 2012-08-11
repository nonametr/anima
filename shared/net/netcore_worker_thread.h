#ifndef NETCORE_SOCKET_THREAD_H
#define NETCORE_SOCKET_THREAD_H

#include "common.h"
#include "socket.h"
#include "thread_core.h"
#include "net_core.h"
#include "thread.h"
#include "socket_base.h"

#define THREAD_EVENT_MAX_SIZE 128  /// This is the number of socket events each thread can receieve at once.

class NetCoreWorkerThread : public Thread
{
    friend class NetCore;
public:
    NetCoreWorkerThread();
    virtual ~NetCoreWorkerThread()
    {
        close ( _epoll_inst );
    };
    void run();
    void onShutdown()
    {
        _running = false;
        while (!_running) {
            sleep(1);
        }
    }
    void addToEpoll ( SOCKET sock );
    void removeFromEpoll ( SOCKET sock );
    static void init();
    static NetCoreWorkerThread* getOptimal();
private:
    /// epoll event struct
    int _epoll_inst;
    struct epoll_event _events[THREAD_EVENT_MAX_SIZE];
    volatile bool _running;

    static AtomicCounter *_max_thr;
    static AtomicCounter *_optimal_thr_id;
    static NetCoreWorkerThread **_thr;
};

#endif // NETCORE_SOCKET_THREAD_H
