#ifndef NETCORE_H
#define NETCORE_H

#include "singleton.h"
#include "socket.h"
#include "thread.h"
#include "common.h"
#include "netcore_worker_thread.h"

/// This default value should be more than enough.
#define SOCKET_LISTEN_MAX_COUNT 128
#define SOCKET_MAX_COUNT 32768	    /// This number dont need to be too big, otherwise it's gonna be eating
/// memory. 32768 = 256KB, so thats no big issue for now

// #define ANTI_DDOS 8//DONT WORK BEHIND PROXY SUCH AS NGINX

class ListenSocket;
class NetCoreWorkerThread;

class NetCore : public Singleton<NetCore>
{
    friend class NetCoreWorkerThread;
    friend class Socket;
public:
    NetCore();
    virtual ~NetCore();

    /// add a new socket to the r/w epoll set and to the sock mapping
    void addSocket ( Socket * s );
    void addListenSocket ( ListenSocket * s );
private:
    Socket *getSock ( SOCKET sock )
    {
        return _rw_sock[sock];
    };
    ListenSocket *getListenSock ( SOCKET sock )
    {
        return _listen_sock[sock];
    };
    /// closes all sockets
    void closeAll();
    void addToEpoll ( SOCKET sock );
    void removeFromEpoll ( SOCKET sock );
    /// remove a socket from epoll r/w set/sock mapping
    void removeSocket ( Socket * s );

    uint32 _listen_sock_count;
    uint32 _sock_count;
    uint32 _max_sock_desc;

    associative_container<SOCKET, NetCoreWorkerThread*> _netcore_threads;
    Socket* _rw_sock[SOCKET_MAX_COUNT];
    ListenSocket* _listen_sock[SOCKET_LISTEN_MAX_COUNT];
};

#define iNetCore NetCore::getSingletonPtr()

#endif // NETCORE_H
