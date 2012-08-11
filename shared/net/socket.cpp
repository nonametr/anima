#include "socket.h"
#include <zlib.h>
#include "net_core.h"
#include "listen_socket.h"
#include <stdio.h>

#define CROSSDOMAIN "<cross-domain-policy>\
 <site-control permitted-cross-domain-policies=\"all\"/>\
 <allow-access-from domain=\"*\" to-ports=\"*\"/>\
 <allow-http-request-headers-from domain=\"*\" headers=\"*\"/>\
</cross-domain-policy>"

Socket::Socket() :  _type ( DEFAULT_SOCKET ), _connected ( false )
{
    _sock = create();
    ASSERT_CONTINUE ( _sock > 0 );
    content_length = 0;
}
Socket::~Socket()
{
}
void Socket::connect ( const char * address, uint32 port )
{
    struct hostent * host = gethostbyname ( address );
    ASSERT_RETURN ( host != 0 );

    _client.sin_family = host->h_addrtype;
    _client.sin_port = ntohs ( ( u_short ) port );
    memcpy ( &_client.sin_addr.s_addr, host->h_addr_list[0], host->h_length );

    //disableBlocking();//in _onConnect
    ASSERT_RETURN ( ::connect ( _sock, ( const sockaddr* ) &_client, sizeof ( _client ) ) != -1 );
    _onConnect();
}
void Socket::disconnect()
{
    _onDisconnect();
    closeSocket();
}
void Socket::accept ( sockaddr_in * address )
{
    memcpy ( &_client, address, sizeof ( *address ) );
    _onConnect();
}
void Socket::send ( Packet *pkt )
{
    char *send_buf = new char[pkt->total_size];
    memcpy ( send_buf, pkt, PACKET_HEADER_SIZE );
    memcpy ( &send_buf[PACKET_HEADER_SIZE], pkt->data.c_str(), pkt->data.size() );
    uint send_count = 0;
    while ( send_count < pkt->total_size )
    {
        send_count += ::send ( _sock, &send_buf[send_count], pkt->total_size - send_count, MSG_NOSIGNAL );
    }
    delete []send_buf;
}
void Socket::send ( const char* out_packet, uint32 size )
{
    int just_send = 0;
    int send_count = 0;
    while ( send_count < ( int ) size )
    {
        just_send = ::send ( _sock, &out_packet[send_count], ( size - send_count > 255 ) ?255:size - send_count, MSG_NOSIGNAL );
        if ( just_send > 0 )
        {
            send_count += just_send;
        }
    }
}
void Socket::read()
{
    int read_size = 0;
    bool connect_init = false;
    if ( data.empty() )
    {
        connect_init = true;
        content_length = 0;
    }
    do
    {
        read_size = recv ( _sock, &_recv_buf, RECIVE_BUFFER_SIZE, 0 );
        if ( read_size <= 0 )
            break;
        else
            data.append ( _recv_buf, read_size );
    }
    while ( true );
    if ( data.empty() )
    {
        traceerr ( "Error rcv packet size 0" );
        if ( this->isConnected() )
        {
            this->disconnect();
        }
        return;
    }
    if ( connect_init )
    {
        size_t str_pos;
        switch ( _type )
        {
        case DEFAULT_SOCKET:
            break;
        case HTTP_SOCKET:
            str_pos = data.find ( "Content-Length:" );
            if ( str_pos != string::npos )
            {
                sscanf ( data.c_str() + str_pos, "Content-Length: %u\r\n", &content_length );
                str_pos = data.find ( "friends_vk_req_friends_post" );
                if ( str_pos != string::npos )
                    break;
                content_length += str_pos;
            }
            break;
        }
    }
    if ( content_length <= data.size() )
    {
        Packet *pkt = new Packet;
        switch ( _type )
        {
        case DEFAULT_SOCKET:
            if ( data.size() < PACKET_HEADER_SIZE )
            {
                traceerr ( "Error rcv packet without header" );
                if ( this->isConnected() )
                {
                    Packet send_pkt = OG_ERROR::create ( 0, intToString ( MSG_PACKET_NO_HEADER ).c_str() );
                    this->send ( &send_pkt );
                    this->disconnect();
                }
                return;
            }
            memcpy ( &pkt->type, &data.c_str() [0*PACKET_INT_SIZE], PACKET_INT_SIZE );
            memcpy ( &pkt->total_size, &data.c_str() [1*PACKET_INT_SIZE], PACKET_INT_SIZE );
            memcpy ( &pkt->data_size, &data.c_str() [2*PACKET_INT_SIZE], PACKET_INT_SIZE );
            memcpy ( &pkt->crc32, &data.c_str() [3*PACKET_INT_SIZE], PACKET_INT_SIZE );
            memcpy ( &pkt->packet_id, &data.c_str() [4*PACKET_INT_SIZE], PACKET_INT_SIZE );
            if ( data.find ( "policy-file-request" ) != string::npos )
            {
                this->send ( CROSSDOMAIN, strlen ( CROSSDOMAIN ) );
                this->disconnect();
                return;
            }
            if ( pkt->data_size != data.size() - PACKET_HEADER_SIZE )
            {
                traceerr ( "Error rcv packet fragmented or corrupted. Can't handle it! Current frame buffer = %s", data.c_str() );
                Packet send_pkt = OG_ERROR::create ( 0, intToString ( MSG_PACKET_FRAGMET ).c_str() );
                this->send ( &send_pkt );
                this->disconnect();
                delete pkt;
                return;
            }
            pkt->data = data.substr ( PACKET_HEADER_SIZE );
            pkt->sock = this;
            break;
        case HTTP_SOCKET:
            pkt->data = data;
            pkt->sock = this;
            break;
        }
        _onRead ( pkt );
        data.clear();
    }
}
void Socket::setOwner ( ListenSocket *owner )
{
    _owner = owner;
}
void Socket::_onRead ( Packet *pkt )
{
    if ( _owner )
        _owner->_onPacketRead ( pkt );
}
void Socket::_onConnect()
{
    /// set common parameters on the socket file descriptor
    disableBlocking();
    disableBuffering();

    _connected = true;

    if ( _owner )
        _owner->_onPacketConnect ( this );

    iNetCore->addSocket ( this );
}
void Socket::_onDisconnect()
{
    if ( !_connected )
        return;
    _connected = false;
    /// remove from netcore
    iNetCore->removeSocket ( this );
    if ( _owner )
        _owner->_onPacketDisconnect ( this );
}
string Socket::getRemoteIP()
{
    char* ip = ( char* ) inet_ntoa ( _client.sin_addr );
    if ( ip != NULL )
        return string ( ip );
    else
        return string ( "noip" );
}


