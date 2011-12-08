#ifndef LISTENSOCKET_H
#define LISTENSOCKET_H

#include "net_core.h"
#include "socket.h"

class ListenSocket : public Socket
{
      friend class NetCoreWorkerThread;
public:
    ListenSocket(const char* listen_address, uint port)
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
    virtual void onClientRead(const Client *pkt) {}
private:
    ListenSocket(){};
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
    uint len;

    Socket* rw_socket;
};

#endif // LISTENSOCKET_H

