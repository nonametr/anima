#include "socket.h"
#include "net_core.h"

#include "listen_socket.h"

Socket::Socket() : _connected(false)
{
    _owner = NULL;
    _sock = create();
    _connected.setVal(false);
    ASSERT_CONTINUE(_sock > 0);
}
Socket::~Socket()
{
}
void Socket::connect(const char * address, uint32 port)
{
    struct hostent * host = gethostbyname(address);
    ASSERT_RETURN(host != 0);

    _client.sin_family = host->h_addrtype;
    _client.sin_port = ntohs((u_short)port);
    memcpy(&_client.sin_addr.s_addr, host->h_addr_list[0], host->h_length);

    //disableBlocking();//in _onConnect
    ASSERT_RETURN(::connect(_sock, (const sockaddr*)&_client, sizeof(_client)) != -1);
    _onConnect();
}
void Socket::disconnect()
{
    _onDisconnect();
    closeSocket();
}
void Socket::accept(sockaddr_in * address)
{
    memcpy(&_client, address, sizeof(*address));
    _onConnect();
}
void Socket::send(const char* out_packet, uint32 size)
{
    if (::send(_sock, out_packet, size*sizeof(char), MSG_NOSIGNAL) == -1)
        traceerr("Error on send");
}
void Socket::read()
{
    int pack_type;
    int pack_size;

    int bytes_recv = recv(_sock, _recv_buf, RECIVE_BUFFER_SIZE, 0);

    ///packet type and packet size must be here
    if (bytes_recv < PACKET_HEADER_SIZE)
    {
        traceerr("Error rcv packet without header");
        this->send(MSG_PACKET_NO_HEADER, strlen(MSG_PACKET_NO_HEADER));
        this->disconnect();
    }
    memcpy(&pack_type, &_recv_buf[0], PACKET_INT_SIZE);
    memcpy(&pack_size, &_recv_buf[PACKET_INT_SIZE], PACKET_INT_SIZE);

    if (pack_type >= IG_MAX_ID)
    {
        traceerr("Error rcv packet with id graiter than possible. Can't handle it!");
        this->send(MSG_PACKET_WRONG_ID, strlen(MSG_PACKET_NO_HEADER));
        this->disconnect();
    }
    if (bytes_recv != pack_size)
    {
        traceerr("Error rcv packet fragmented or corrupted. Can't handle it!");
        this->send(MSG_PACKET_FRAGMET, strlen(MSG_PACKET_NO_HEADER));
        this->disconnect();
    }
    ClientConnection *pkt = new ClientConnection;
    pkt->sock = this;
    pkt->size = pack_size;
    pkt->type = pack_type;
    pkt->data = new char[pack_size];
    memcpy(pkt->data, &_recv_buf, pack_size);

    _onRead(pkt);
}
void Socket::setOwner(ListenSocket *owner)
{
    _owner = owner;
}
void Socket::_onRead( ClientConnection *pkt )
{
    if (_owner)
        _owner->_onClientConnectionRead(pkt);
}
void Socket::_onConnect()
{
    /// set common parameters on the socket file descriptor
    disableBlocking();
    disableBuffering();

    _connected.setVal(true);

    iNetCore->addSocket(this);
    if (_owner)
        _owner->_onClientConnectionConnect(this);
}
void Socket::_onDisconnect()
{
    _connected.setVal(false);
    /// remove from netcore
    iNetCore->removeSocket(this);
    if (_owner)
        _owner->_onClientConnectionDisconnect(this);
}
string Socket::getRemoteIP()
{
    char* ip = (char*)inet_ntoa( _client.sin_addr );
    if ( ip != NULL )
        return string( ip );
    else
        return string( "noip" );
}

