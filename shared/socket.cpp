#include "socket.h"

Socket::Socket() : _connected(false)
{
    _sock = create();
    ASSERT_CONTINUE(_sock < 0);
}
Socket::~Socket()
{
}
bool Socket::connect(const char * address, uint port)
{
    struct hostent * host = gethostbyname(address);
    ASSERT_RETURN(host != 0);

    _client.sin_family = host->h_addrtype;
    _client.sin_port = ntohs((u_short)port);
    memcpy(&_client.sin_addr.s_addr, host->h_addr_list[0], host->h_length);

    //disableBlocking();
    ASSERT_RETURN(::connect(_sock, (const sockaddr*)&_client, sizeof(_client)) != -1);
    _onConnect();
    return true;
}
bool Socket::disconnect()
{
    _onDisconnect();
    closeSocket();
}
bool Socket::accept(sockaddr_in * address)
{
    memcpy(&_client, address, sizeof(*address));
    _onConnect();
}
bool Socket::send()
{

    return true;
}
bool Socket::_onConnect()
{
    /// set common parameters on the socket file descriptor
    disableBlocking();
    disableBuffering();

    _connected = true;

    //sSocketMgr.AddSocket(this);

    /// Call virtual onconnect
    onConnect();
}
bool Socket::_onDisconnect()
{
    _connected = false;
    // remove from mgr
    //sSocketMgr.RemoveSocket(this);
    onDisconnect();
}
string Socket::getRemoteIP()
{
    char* ip = (char*)inet_ntoa( _client.sin_addr );
    if ( ip != NULL )
        return string( ip );
    else
        return string( "noip" );
}

