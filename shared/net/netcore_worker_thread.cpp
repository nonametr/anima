#include "netcore_worker_thread.h"
#include "listen_socket.h"
#include "server.h"

AtomicCounter* NetCoreWorkerThread::_max_thr = new AtomicCounter();
AtomicCounter* NetCoreWorkerThread::_optimal_thr_id = new AtomicCounter();
NetCoreWorkerThread **NetCoreWorkerThread::_thr = NULL;

void NetCoreWorkerThread::init()
{
    _thr = new NetCoreWorkerThread*[iServer->getNumNetThreads()];
    _optimal_thr_id->setVal(iServer->getNumNetThreads());
    for ( uint32 i = 0; i < iServer->getNumNetThreads(); ++i )
    {
        iThreadCore->startThread ( new NetCoreWorkerThread );
    }
}
NetCoreWorkerThread* NetCoreWorkerThread::getOptimal()
{
    int opt_id = _optimal_thr_id->getVal() - 1;
    if (opt_id >= 0)
    {
        _optimal_thr_id->setVal(opt_id);
    }
    else
    {
        opt_id = _max_thr->getVal() - 1;
        _optimal_thr_id->setVal(opt_id);
    }
    return  _thr[opt_id];
}
NetCoreWorkerThread::NetCoreWorkerThread() : _running(true)
{
    _thr[_max_thr->getVal()] = this;
    ++(*_max_thr);
    _epoll_inst = epoll_create ( SOCKET_MAX_COUNT );
    if ( _epoll_inst == -1 )
    {
        traceerr ( "Could not create epoll instance (/dev/epoll)." );
        exit ( -1 );
    }
}
void NetCoreWorkerThread::addToEpoll ( SOCKET sock )
{
    /// Add epoll event based on socket activity.
    struct epoll_event ev;
    memset ( &ev, 0, sizeof ( epoll_event ) );
    ev.events = EPOLLIN;
    ev.data.fd = sock;

    if ( epoll_ctl ( _epoll_inst, EPOLL_CTL_ADD, ev.data.fd, &ev ) )
        traceerr ( "Could not add event to epoll_set sock %u", sock );
}
void NetCoreWorkerThread::removeFromEpoll ( SOCKET sock )
{
    /// Remove from epoll list.
    struct epoll_event ev;
    memset ( &ev, 0, sizeof ( epoll_event ) );
    ev.data.fd = sock;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLHUP | EPOLLONESHOT;

    if ( epoll_ctl ( _epoll_inst, EPOLL_CTL_DEL, ev.data.fd, &ev ) )
        traceerr ( "Could not remove sock %u from epoll set", sock );
}
void NetCoreWorkerThread::run()
{
    int sock_count;
    Socket* ptr;

    while ( _running )
    {
        sock_count = epoll_wait ( _epoll_inst, _events, THREAD_EVENT_MAX_SIZE, 5000 );
        if (sock_count == -1)
            traceerr("%s", "Error on EPOLL_WAIT!");
        for ( int i = 0; i < sock_count; ++i )
        {
            if ( _events[i].data.fd >= SOCKET_MAX_COUNT )
            {
                traceerr ( "Requested sock that is too high (%u)", _events[i].data.fd );
                continue;
            }

            ptr = iNetCore->getSock ( _events[i].data.fd );

            if ( ptr == NULL )
            {
                if ( _events[i].data.fd >= SOCKET_LISTEN_MAX_COUNT )
                {
                    traceerr ( "Requested sock that is too high (%u)", _events[i].data.fd );
                    continue;
                }
                if ( ( ptr = ( ( ListenSocket* ) iNetCore->getListenSock ( _events[i].data.fd ) ) ) != NULL )
                    ( ( ListenSocket* ) ptr )->onAccept();
                else
                    traceerr ( "Returned invalid sock obj (no pointer) of sock %u", _events[i].data.fd );
                continue;
            }
            if ( _events[i].events & EPOLLHUP || _events[i].events & EPOLLRDHUP || _events[i].events & EPOLLERR )
            {
                ptr->disconnect();
                continue;
            }
            else if ( _events[i].events & EPOLLIN )
            {
                if ( !ptr->isConnected() )
                {
                    traceerr ( "Invalid sock obj (disconnected) of sock %u", _events[i].data.fd );
                    continue;
                }
                ptr->read();
            }
        }
    }
    _running = !_running;
}
