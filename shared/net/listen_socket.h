#ifndef LISTENSOCKET_H
#define LISTENSOCKET_H

#include "net_core.h"
#include "socket.h"

class ListenSocket : public Socket
{
    friend class Socket;
    friend class NetCoreWorkerThread;
public:
    ListenSocket(const char* listen_address, uint32 port)
    {
        reuseAddr();
        disableBlocking();
        setTimeout(60);

        listen_socket_address.sin_family = AF_INET;
        listen_socket_address.sin_port = ntohs((u_short)port);
        listen_socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
        listen_socket_opened = false;

        if (strcmp(listen_address, "0.0.0.0"))
        {
            struct hostent* hostname = gethostbyname(listen_address);
            if (hostname != 0)
                memcpy(&listen_socket_address.sin_addr.s_addr, hostname->h_addr_list[0], hostname->h_length);
        }

        // bind.. well attempt to.
        int ret = ::bind(_sock, (const sockaddr*)&listen_socket_address, sizeof(listen_socket_address));
        if (ret != 0)
        {
            traceerr("Bind unsuccessful on port %u.", (unsigned int)port);
            return;
        }

        ret = listen(_sock, 5);
        if (ret != 0)
        {
            traceerr("Unable to listen on port %u.", (unsigned int)port);
            return;
        }
        len = sizeof(sockaddr_in);
        listen_socket_opened = true;
        iNetCore->addListenSocket(this);
    }
    virtual ~ListenSocket()
    {
        if (listen_socket_opened)
            close();
    }
    ClientConnection* paketize(char *pkt_data, int bytes_recv, Socket *sock)
    {
        int pack_type;
        int pack_size;
        ///packet type and packet size must be here
        if (bytes_recv < PACKET_HEADER_SIZE)
        {
            traceerr("Error rcv packet without header");
            sock->send(MSG_PACKET_NO_HEADER, strlen(MSG_PACKET_NO_HEADER));
            sock->disconnect();
        }
        memcpy(&pack_type, &pkt_data[0], PACKET_INT_SIZE);
        memcpy(&pack_size, &pkt_data[PACKET_INT_SIZE], PACKET_INT_SIZE);

        if (pack_type >= IG_MAX_ID)
        {
            traceerr("Error rcv packet with id graiter than possible. Can't handle it!");
            sock->send(MSG_PACKET_WRONG_ID, strlen(MSG_PACKET_NO_HEADER));
            sock->disconnect();
        }
        if (bytes_recv != pack_size)
        {
            traceerr("Error rcv packet fragmented or corrupted. Can't handle it!");
            sock->send(MSG_PACKET_FRAGMET, strlen(MSG_PACKET_NO_HEADER));
            sock->disconnect();
        }
        ClientConnection *pkt = new ClientConnection;
        pkt->sock = sock;
        pkt->data_size = pack_size - 3*sizeof(int);///3 ints - service data;
        pkt->type = pack_type;
        pkt->data = new char[pkt->data_size];
        memcpy(pkt->data, &pkt_data[3*sizeof(int)], pkt->data_size);
	delete [] pkt_data;
	return pkt;
    }
    virtual void onClientConnectionRead(char *pkt_data, int bytes_recv, Socket *sock) = 0;
    virtual void onClientConnectionDisconnect(Socket *sock) = 0;
    virtual void onClientConnectionConnect(Socket *sock) = 0;
private:
    inline void _onClientConnectionRead(char *pkt_data, int bytes_recv, Socket *sock)
    {
        this->onClientConnectionRead(pkt_data, bytes_recv, sock);
    }
    inline void _onClientConnectionDisconnect(Socket *sock)
    {
        this->onClientConnectionDisconnect(sock);
    }
    inline void _onClientConnectionConnect(Socket *sock)
    {
        this->onClientConnectionConnect(sock);
    }
    ListenSocket() {};
    void onAccept()
    {
        accept_socket = ::accept(_sock, (sockaddr*)&accept_socket_address, (socklen_t*)&len);
        if (accept_socket == -1)
            return;

        rw_socket = new Socket(accept_socket);
        rw_socket->setOwner(this);
        rw_socket->accept(&accept_socket_address);
    }
    void close()
    {
        if (listen_socket_opened)
            closeSocket();
        listen_socket_opened = false;
    }
    SOCKET accept_socket;
    struct sockaddr_in listen_socket_address;
    struct sockaddr_in accept_socket_address;
    bool listen_socket_opened;
    uint32 len;

    Socket* rw_socket;
};

#endif // LISTENSOCKET_H

