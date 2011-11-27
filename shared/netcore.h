#ifndef NETCORE_H
#define NETCORE_H

#include "singleton.h"
#include "socket.h"
#include "thread.h"

#define SOCKET_LISTEN_MAX_COUNT 128
#define SOCKET_RW_MAX_COUNT 16384	    /// This number dont need to be too big, otherwise you're gonna be eating
/// memory. 16384 = 128KB, so thats no big issue for now, and I really can't
/// see anyone wanting to have more than 16384 concurrent connections.
class NetCore : public Singleton<NetCore>
{

public:
    NetCore();
    virtual ~NetCore();

    /// add a new socket to the r/w epoll set and to the sock mapping
    void addSocket(Socket * s);
    void addListenSocket(Socket * s);

    /// remove a socket from epoll r/w set/sock mapping
    void removeSocket(Socket * s);
private:
    // fd -> pointer binding.
    Socket * _rw_sock[SOCKET_RW_MAX_COUNT];
    Socket * _listen_sock[SOCKET_LISTEN_MAX_COUNT];
};

// class SocketReaderThread : public Thread
// {
// public:
//     bool run();
//     void OnShutdown()
//     {
//         _running = false;
//     }
// private:
//     /// epoll event struct
//     struct epoll_event _events[THREAD_EVENT_SIZE];
//     bool _running;
// };
#define iNetCore NetCore::getSingletonPtr()

#endif // NETCORE_H
