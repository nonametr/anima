#include "net_core.h"
#include "listen_socket.h"
#include "config.h"
#include "thread_core.h"
#include "server.h"

initialiseSingleton ( NetCore );

NetCore::NetCore()
{
    /// null out the pointer array
    memset ( _rw_sock, 0, sizeof ( void* ) * SOCKET_MAX_COUNT );
    memset ( _listen_sock, 0, sizeof ( void* ) * SOCKET_LISTEN_MAX_COUNT );
    _max_sock_desc = 0;

    NetCoreWorkerThread::init();
}
NetCore::~NetCore()
{
    for ( uint32 i = 0; i < SOCKET_LISTEN_MAX_COUNT; ++i )
    {
        if ( _listen_sock[i] )
            delete _listen_sock[i];
    }
    for ( uint32 i = 0; i < SOCKET_MAX_COUNT; ++i )
    {
        if ( _rw_sock[i] )
            delete _rw_sock[i];
    }
    closeAll();
}
void NetCore::addToEpoll ( SOCKET sock )
{
    NetCoreWorkerThread *thr = NetCoreWorkerThread::getOptimal();
    _netcore_threads[sock] = thr;
    thr->addToEpoll(sock);
}
void NetCore::removeFromEpoll ( SOCKET sock )
{
    auto thr_it = _netcore_threads.find(sock);
    if (thr_it != _netcore_threads.end())
    {
        thr_it->second->removeFromEpoll(sock);
    }
}
void NetCore::addListenSocket ( ListenSocket * s )
{
    ASSERT ( _listen_sock[s->getSockDescriptor() ] == NULL );
    _listen_sock[s->getSockDescriptor() ] = s;
    ++_listen_sock_count;

    addToEpoll ( s->getSockDescriptor() );
}
void NetCore::addSocket ( Socket * s )
{
#ifdef ANTI_DDOS
    uint32 saddr = s->getRemoteAddress().s_addr;
    int count;
    for ( uint32 i = 0; i < _max_sock_desc; ++i )
    {
        if ( _rw_sock[i]->getRemoteAddress().s_addr == saddr )
            count++;
    }
    /// More than ANTI_DDOS num. connections from the same ip? enough! xD
    if ( count > ANTI_DDOS )
    {
	traceerr("Error DDOS detected! User droped!")
        s->disconnect();
        return;
    }
#endif
    if ( s->getSockDescriptor() > (int)_max_sock_desc )
        _max_sock_desc = s->getSockDescriptor();
    if ( _rw_sock[s->getSockDescriptor() ] != NULL )
    {
        if ( _rw_sock[s->getSockDescriptor() ]->isConnected() )
        {
            traceerr ( "Sock allready in use! Some logic error exist!" );
            s->disconnect();
            _rw_sock[s->getSockDescriptor() ]->disconnect();
            return;
        }
        ///clearing old sock obj. we clear it only if system returns same desc(system nows that its not in use long time ago :)
        delete _rw_sock[s->getSockDescriptor()];
    }
    _rw_sock[s->getSockDescriptor()] = s;
    ++_sock_count;

    addToEpoll ( s->getSockDescriptor() );
}
void NetCore::removeSocket ( Socket* s )
{
    Socket *sock = _rw_sock[s->getSockDescriptor()];
    if ( sock != s )
    {
        traceerr ( "Could not remove sock_desc %u from the set due to its not existing?", s->getSockDescriptor() );
        return;
    }
    --_sock_count;
    
    removeFromEpoll ( s->getSockDescriptor() );
}
void NetCore::closeAll()
{
    for ( uint32 i = 0; i < _max_sock_desc; ++i )
        if ( _rw_sock[i] != NULL )
            _rw_sock[i]->disconnect();
}


