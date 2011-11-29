#ifndef SOCKET_H
#define SOCKET_H

#include "common.h"
#include "socket_base.h"
#include "socket_operations.h"
#include "thread.h"

class Socket : public SocketOperations
{
public:
    Socket(int sock)
    {
      ASSERT_CONTINUE(sock < 0);
      _connected.SetVal(true);
      _sock = sock;
    }
    Socket();
    virtual ~Socket();

    /// Open a connection to another machine
    bool connect(const char * address, uint port);
    /// Disconnect the socket
    bool disconnect();
    /// Accept from connection
    bool accept(sockaddr_in * address);
    /// Locks sending mutex, send bytes, unlocks mutex
    bool send(std::string out_packet);

    /// Called when data is received
    virtual bool onRead() {};
    /// Called when a connection is first successfully established
    virtual bool onConnect() {};
    /// Called when the socket is disconnected from the client (either forcibly or by the connection dropping)
    virtual bool onDisconnect() {};

    string getRemoteIP();
    inline uint getRemotePort() { return ntohs(_client.sin_port); }
    inline in_addr getRemoteAddress() { return _client.sin_addr; }

protected:
    bool _onConnect();
    bool _onDisconnect();
private:
    AtomicBoolean _connected;
    sockaddr_in _client;
};

#endif // SOCKET_H
