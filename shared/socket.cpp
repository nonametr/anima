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
    if (::send(_sock, out_packet.c_str(), out_packet.length()*sizeof(char), MSG_NOSIGNAL) == -1)
        traceerr("Error on send");
    return true;
}
bool Socket::read()
{
    int pack_type;
    int pack_size;
    
    int bytes_recv = recv(_sock, _recv_buf, RECIVE_BUFFER_SIZE, 0);
    ///packet type and packet size must be here
    if (bytes_recv < PACKET_HEADER_SIZE)
    {
        traceerr("Error rcv packet without header");
	this->send(MSG_PACKET_NO_HEADER);
	this->disconnect();
        return false;
    }
    memcpy(&pack_type, &_recv_buf[0], PACKET_INT_SIZE);
    memcpy(&pack_size, &_recv_buf[PACKET_INT_SIZE], PACKET_INT_SIZE);

    if(pack_type >= PACKETS_MAX_ID)
    {
	traceerr("Error rcv packet with id graiter than possible. Can't handle it!");
	this->send(MSG_PACKET_WRONG_ID);
	this->disconnect();
        return false;
    }
    if(bytes_recv < pack_size)
    {
        traceerr("Error rcv packet fragmented or corrupted. Can't handle it!");
	this->send(MSG_PACKET_FRAGMET);
	this->disconnect();
        return false;
    }
    Client *pkt = new Client;
    pkt->connection = this;
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
bool Socket::_onRead( const Client *pkt )
{
    if (_owner)
        _owner->onClientRead(pkt);
    onRead(pkt);
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

