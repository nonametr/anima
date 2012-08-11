#ifndef LISTENSOCKET_H
#define LISTENSOCKET_H

#include "socket.h"
#include "net_core.h"


class ListenSocket : public Socket
{
    friend class Socket;
    friend class NetCoreWorkerThread;
public:
    ListenSocket(const char* listen_address, uint32 port)
    {
        reuseAddr();
        disableBlocking();
 	disableBuffering();
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

        ret = listen(_sock, 128);
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
    virtual void onPacketRead(Packet *pkt) = 0;
    virtual void onPacketDisconnect(Socket *sock) = 0;
    virtual void onPacketConnect(Socket *sock) = 0;
private:
    inline void _onPacketRead(Packet *pkt)
    {
        this->onPacketRead(pkt);
    }
    inline void _onPacketDisconnect(Socket *sock)
    {
        this->onPacketDisconnect(sock);
    }
    inline void _onPacketConnect(Socket *sock)
    {
        this->onPacketConnect(sock);
    }
    ListenSocket() {};
    void onAccept()
    {
        accept_socket = ::accept(_sock, (sockaddr*)&accept_socket_address, (socklen_t*)&len);
        if (accept_socket == -1)
            return;

        rw_socket = new Socket(accept_socket);
	rw_socket->setType(this->getType());
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

