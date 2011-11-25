#ifndef SOCKET_BASE_H
#define SOCKET_BASE_H

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netdb.h>

#define SOCKET int

class SocketBase
{
public:
  SocketBase(){};
  virtual ~SocketBase(){};
protected:
    SOCKET _sock;
};

#endif
