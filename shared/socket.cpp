#include "socket.h"
#include "net_core.h"

#include "listen_socket.h"

Socket::Socket() : _connected(false)
{
    _owner = NULL;
    _sock = create();
    _connected.SetVal(false);
    ASSERT_CONTINUE(_sock > 0);
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

    //disableBlocking();//in _onConnect
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
bool Socket::send(std::string out_packet)
{
    ::send(_sock, out_packet.c_str(), out_packet.length()*sizeof(char), MSG_NOSIGNAL);
    return true;
}
bool Socket::read()
{
    int bytes_recv = recv(_sock, _recv_buf, RECIVE_BUFFER_SIZE, 0);
    _recv_str.assign(_recv_buf, 0, bytes_recv);
    _onRead(_recv_str);
}
void Socket::setOwner(ListenSocket *owner)
{
    _owner = owner;
}
bool Socket::_onRead( const string &data )
{
    if (_owner)
        _owner->onClientRead(data);
    onRead(data);
}
bool Socket::_onConnect()
{
    /// set common parameters on the socket file descriptor
    disableBlocking();
    disableBuffering();

    _connected.SetVal(true);

    iNetCore->addSocket(this);

    /// Call virtual onconnect
    onConnect();
}
bool Socket::_onDisconnect()
{
    _connected.SetVal(false);
    /// remove from netcore
    iNetCore->removeSocket(this);
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

