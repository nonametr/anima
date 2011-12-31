#ifndef SOCKET_OPERATIONS_H
#define SOCKET_OPERATIONS_H

#include "socket_base.h"

class SocketOperations : public SocketBase
{
public:
    SocketOperations() {};
    virtual ~SocketOperations() {};
    /// Create file descriptor for socket i/o operations
    SOCKET create()
    {
        /// create a socket for use with overlapped i/o
        return socket(AF_INET, SOCK_STREAM, 0);
    }
    /// Disable blocking send/recv calls.
    bool disableBlocking()
    {
        uint32 arg = 1;
        return (::ioctl(_sock, FIONBIO, &arg) == 0);
    }
    /// Disable nagle buffering algorithm
    bool disableBuffering()
    {
        uint32 arg = 1;
        return (setsockopt(_sock, 0x6, 0x1, (const char*)&arg, sizeof(arg)) == 0);
    }
    /// Enable nagle buffering algorithm
    bool enableBuffering()
    {
        uint32 arg = 0;
        return (setsockopt(_sock, 0x6, 0x1, (const char*)&arg, sizeof(arg)) == 0);
    }
    /// Set internal buffer size to socket
    bool setSendBufferSize(uint32 size)
    {
        return (setsockopt(_sock, SOL_SOCKET, SO_SNDBUF, (const char*)&size, sizeof(size)) == 0);
    }
    /// Set internal buffer size to socket
    bool setRecvBufferSize(uint32 size)
    {
        return (setsockopt(_sock, SOL_SOCKET, SO_RCVBUF, (const char*)&size, sizeof(size)) == 0);
    }
    /// Set internal timeout.
    bool setTimeout(uint32 timeout)
    {
        struct timeval to;
        to.tv_sec = timeout;
        to.tv_usec = 0;
        if (setsockopt(_sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&to, (socklen_t)sizeof(to)) != 0) return false;
        return (setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&to, (socklen_t)sizeof(to)) == 0);
    }
    /// Set socket keep alive
    bool setKeepAlive()
    {
        uint32 arg = 1;
        return setsockopt( _sock, SOL_SOCKET, SO_KEEPALIVE, (const char*)&arg, sizeof(arg));
    }
    /// Closes a socket fully
    void closeSocket()
    {
        shutdown(_sock, SHUT_RDWR);
        close(_sock);
    }
    /// Sets reuseaddr
    void reuseAddr()
    {
        uint32 option = 1;
        setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&option, 4);
    }
};

#endif

