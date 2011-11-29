#include "netcore.h"
#include "listensocket.h"

initialiseSingleton ( NetCore );

NetCore::NetCore()
{
    _epoll_inst = epoll_create(SOCKET_MAX_COUNT);
    if (_epoll_inst == -1)
    {
        traceerr("Could not create epoll instance (/dev/epoll).");
        exit(-1);
    }
    /// null out the pointer array
    memset(_rw_sock, 0, sizeof(void*) * SOCKET_MAX_COUNT);
    memset(_listen_sock, 0, sizeof(void*) * SOCKET_MAX_COUNT);
    _max_sock_desc = 0;
}
NetCore::~NetCore()
{

}
void NetCore::addToEpoll(SOCKET sock)
{
    /// Add epoll event based on socket activity.
    struct epoll_event ev;
    memset(&ev, 0, sizeof(epoll_event));
    ev.events = EPOLLIN | EPOLLET;		/** use edge-triggered instead of level-triggered because we're using nonblocking sockets */
    ev.data.fd = sock;

    if (epoll_ctl(_epoll_inst, EPOLL_CTL_ADD, ev.data.fd, &ev))
        traceerr("Could not add event to epoll set on sock %u", sock);
}
void NetCore::removeFromEpoll(SOCKET sock)
{
    /// Remove from epoll list.
    struct epoll_event ev;
    memset(&ev, 0, sizeof(epoll_event));
    ev.data.fd = sock;
    ev.events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLHUP | EPOLLONESHOT;

    if (epoll_ctl(_epoll_inst, EPOLL_CTL_DEL, ev.data.fd, &ev))
        traceerr("Could not remove sock %u from epoll set", sock);
}
void NetCore::addListenSocket(ListenSocketBase * s)
{
    ASSERT_CONTINUE(_listen_sock[s->getSockDescriptor()] == 0);
    _listen_sock[s->getSockDescriptor()] = s;
    ++_listen_sock_count;

    addToEpoll(s->getSockDescriptor());
}
void NetCore::addSocket(Socket * s)
{
#ifdef ANTI_DDOS
    uint saddr;
    int i, count;
    for (uint i = 0; i < _max_sock_desc; ++i)
    {
        if (_rw_sock[i]->getRemoteAddress().s_addr == saddr)
            count++;
    }
    /// More than ANTI_DDOS num. connections from the same ip? enough! xD
    if (count > ANTI_DDOS)
    {
        s->disconnect();
        return;
    }
#endif
    if (s->getSockDescriptor() > _max_sock_desc)
        _max_sock_desc = s->getSockDescriptor();
    if (_rw_sock[s->getSockDescriptor()] != NULL)
    {
        traceerr("Sock allready in use! Some logic error exist!");
        s->disconnect();
        return;
    }
    _rw_sock[s->getSockDescriptor()] = s;
    ++_sock_count;

    addToEpoll(s->getSockDescriptor());
}
void NetCore::removeSocket(Socket* s)
{
    if (_rw_sock[s->getSockDescriptor()] != s)
    {
        traceerr("Could not remove sock_desc %u from the set due to it not existing?", s->getSockDescriptor());
        return;
    }
    _rw_sock[s->getSockDescriptor()] = NULL;
    --_sock_count;

    removeFromEpoll(s->getSockDescriptor());
}
void NetCore::closeAll()
{
    for (uint i = 0; i < _max_sock_desc; ++i)
        if (_rw_sock[i] != NULL)
            _rw_sock[i]->disconnect();
}
NetCoreWorkerThread::NetCoreWorkerThread()
{
    _epoll_inst = iNetCore->getEpollInst();
}
void NetCoreWorkerThread::run()
{
    int sock_count;
    Socket* ptr;

    while (_running)
    {
        sock_count = epoll_wait(_epoll_inst, _events, THREAD_EVENT_MAX_SIZE, 5000);
        for (uint i = 0; i < sock_count; ++i)
        {
            if (_events[i].data.fd >= SOCKET_MAX_COUNT)
            {
                traceerr("Requested sock that is too high (%u)", _events[i].data.fd);
                continue;
            }

            ptr = iNetCore->getSock(_events[i].data.fd);

            if (ptr == NULL)
            {
                if (_events[i].data.fd >= SOCKET_LISTEN_MAX_COUNT)
                {
                    traceerr("Requested sock that is too high (%u)", _events[i].data.fd);
                    continue;
                }
                if ((ptr = ((ListenSocketBase*)iNetCore->getListenSock(_events[i].data.fd))) != NULL)
                    ((ListenSocketBase*)ptr)->onAccept();
                else
                    traceerr("Returned invalid sock obj (no pointer) of sock %u", _events[i].data.fd);
                continue;
            }

            if (_events[i].events & EPOLLHUP || _events[i].events & EPOLLERR)
            {
                ptr->disconnect();
                continue;
            }
            else if (_events[i].events & EPOLLIN)
            {
		ptr->onRead();
            }
        }
    }
}


