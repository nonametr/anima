#ifndef NETCORE_H
#define NETCORE_H

#include "singleton.h"
#include "socket.h"
#include "thread.h"

#define THREAD_EVENT_MAX_SIZE 128  /// This is the number of socket events each thread can receieve at once.
                                     /// This default value should be more than enough.
#define SOCKET_LISTEN_MAX_COUNT 128
#define SOCKET_MAX_COUNT 8192	    /// This number dont need to be too big, otherwise it's gonna be eating
 					    /// memory. 8192 = 64KB per 1 thread, so thats no big issue for now

//#define ANTI_DDOS 8//DONT WORK BEHIND PROXY SUCH AS NGINX

class ListenSocketBase;
class NetCoreWorkerThread;

class NetCore : public Singleton<NetCore>
{
public:
    NetCore();
    virtual ~NetCore();

    /// add a new socket to the r/w epoll set and to the sock mapping
    void addSocket(Socket * s);
    void addListenSocket(ListenSocketBase * s);

    int getEpollInst(){ return _epoll_inst; };
    /// remove a socket from epoll r/w set/sock mapping
    void removeSocket(Socket * s);
    /// closes all sockets
    void closeAll();
    void addToEpoll(SOCKET sock);
    void removeFromEpoll(SOCKET sock);
    Socket *getSock(SOCKET sock){ return _rw_sock[sock]; };
    ListenSocketBase *getListenSock(SOCKET sock){ return _listen_sock[sock]; };
private:  
      int _epoll_inst;
      
    uint _listen_sock_count;
    uint _sock_count;
    uint _max_sock_desc;
    NetCoreWorkerThread *_worker_thread;
    Socket* _rw_sock[SOCKET_MAX_COUNT];
    ListenSocketBase* _listen_sock[SOCKET_LISTEN_MAX_COUNT];
};

class NetCoreWorkerThread : public Thread
{
  friend class NetCore;
public:
    NetCoreWorkerThread();
    virtual ~NetCoreWorkerThread(){ close(_epoll_inst); };
    void run();
    void OnShutdown()
    {
        _running = false;
    }
private:
    /// epoll event struct
    int _epoll_inst;
    struct epoll_event _events[THREAD_EVENT_MAX_SIZE];
    bool _running;
};

#define iNetCore NetCore::getSingletonPtr()

#endif // NETCORE_H
