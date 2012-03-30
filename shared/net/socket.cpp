#include "socket.h"
#include <zlib.h>
#include "net_core.h"
#include "listen_socket.h"

Socket::Socket() :  _type(DEFAULT_SOCKET), _connected(false)
{
    _sock = create();
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
void Socket::send(Packet *pkt)
{
    char *send_buf = new char[pkt->total_size];
    memcpy(send_buf, pkt, PACKET_HEADER_SIZE);
    memcpy(&send_buf[PACKET_HEADER_SIZE], pkt->data, pkt->data_size);
    ::send(_sock, send_buf, pkt->total_size, MSG_NOSIGNAL);
    delete []send_buf;
}
void Socket::send(const char* out_packet, uint32 size)
{
    ::send(_sock, out_packet, size, MSG_NOSIGNAL);
}
void Socket::read()
{
    memset(&_recv_buf[0], 0, RECIVE_BUFFER_SIZE);
    int bytes_recv = recv(_sock, _recv_buf, RECIVE_BUFFER_SIZE, 0);

    if (bytes_recv < PACKET_HEADER_SIZE)
    {
        traceerr("Error rcv packet without header");
	Packet send_pkt = OG_STR::create(0, MSG_PACKET_NO_HEADER);
        this->send(&send_pkt);
        this->disconnect();
        return;
    }
    Packet *pkt = new Packet;
    switch (_type)
    {
    case DEFAULT_SOCKET:
        memcpy(&pkt->type, &_recv_buf[0*PACKET_INT_SIZE], PACKET_INT_SIZE);
        memcpy(&pkt->total_size, &_recv_buf[1*PACKET_INT_SIZE], PACKET_INT_SIZE);
        memcpy(&pkt->data_size, &_recv_buf[2*PACKET_INT_SIZE], PACKET_INT_SIZE);
        memcpy(&pkt->crc32, &_recv_buf[3*PACKET_INT_SIZE], PACKET_INT_SIZE);
	memcpy(&pkt->packet_id, &_recv_buf[4*PACKET_INT_SIZE], PACKET_INT_SIZE);
        if (pkt->data_size != bytes_recv - PACKET_HEADER_SIZE)
        {
            traceerr("Error rcv packet fragmented or corrupted. Can't handle it!");
	    Packet send_pkt = OG_STR::create(0, MSG_PACKET_FRAGMET);
            this->send(&send_pkt);
            this->disconnect();
            delete pkt;
            return;
        }
        pkt->data = new char[pkt->data_size];
        memcpy(&pkt->data[0], &_recv_buf[PACKET_HEADER_SIZE], pkt->data_size*sizeof(char));
        pkt->sock = this;
        break;
    case HTTP_SOCKET:
        pkt->data = new char[bytes_recv];
        pkt->data_size = pkt->total_size = bytes_recv;
        memcpy(&pkt->data[0], &_recv_buf[0], pkt->data_size);
        pkt->sock = this;
        break;
    }
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

    _connected = true;

    iNetCore->addSocket(this);
    if (_owner)
        _owner->_onPacketConnect(this);
}
void Socket::_onDisconnect()
{
    _connected = false;
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

