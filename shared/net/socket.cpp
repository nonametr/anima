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
    send_mutex.lock();
    if (::send(_sock, out_packet, size*sizeof(char), MSG_NOSIGNAL) == -1)
        traceerr("Error on send packet!");
    send_mutex.unlock();
}
void Socket::read()
{
    int bytes_recv = recv(_sock, _recv_buf, RECIVE_BUFFER_SIZE, 0);

    if (bytes_recv < PACKET_HEADER_SIZE)
    {
        traceerr("Error rcv packet without header");
        this->send(MSG_PACKET_NO_HEADER, strlen(MSG_PACKET_NO_HEADER));
        this->disconnect();
    }
    
    Packet *pkt = new Packet;
    memcpy(&pkt->type, &_recv_buf[0*PACKET_INT_SIZE], PACKET_INT_SIZE);
    memcpy(&pkt->total_size, &_recv_buf[1*PACKET_INT_SIZE], PACKET_INT_SIZE);
    memcpy(&pkt->data_size, &_recv_buf[2*PACKET_INT_SIZE], PACKET_INT_SIZE);
    memcpy(&pkt->crc32, &_recv_buf[3*PACKET_INT_SIZE], PACKET_INT_SIZE);
    
    if (pkt->data_size != bytes_recv - PACKET_HEADER_SIZE)
    {
        traceerr("Error rcv packet fragmented or corrupted. Can't handle it!");
        this->send(MSG_PACKET_FRAGMET, strlen(MSG_PACKET_NO_HEADER));
        this->disconnect();
        delete pkt;
        return;
    }
    pkt->data = new char[pkt->data_size];
    memcpy(&pkt->data[0], &_recv_buf[4*PACKET_INT_SIZE], pkt->data_size*sizeof(char));
    pkt->sock = this;

    _onRead(pkt);
}
void Socket::setOwner(ListenSocket *owner)
{
    _owner = owner;
}
void Socket::_onRead(Packet *pkt)
{
    if (_owner)
        _owner->_onPacketRead(pkt);
}
void Socket::_onConnect()
{
    /// set common parameters on the socket file descriptor
    disableBlocking();
    disableBuffering();

    _connected.setVal(true);

    iNetCore->addSocket(this);
    if (_owner)
        _owner->_onPacketConnect(this);
}
void Socket::_onDisconnect()
{
    _connected.setVal(false);
    /// remove from netcore
    iNetCore->removeSocket(this);
    if (_owner)
        _owner->_onPacketDisconnect(this);
}
string Socket::getRemoteIP()
{
    char* ip = (char*)inet_ntoa( _client.sin_addr );
    if ( ip != NULL )
        return string( ip );
    else
        return string( "noip" );
}

