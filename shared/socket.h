#ifndef SOCKET_H
#define SOCKET_H

#include "common.h"
#include "socket_base.h"
#include "socket_operations.h"

class Socket : public SocketOperations
{
public:
    Socket();
    virtual ~Socket();

    /// Open a connection to another machine
    bool connect(const char * address, uint port);
    /// Disconnect the socket
    bool disconnect();
    /// Accept from connection
    bool accept(sockaddr_in * address);
    /// Locks sending mutex, send bytes, unlocks mutex
    bool send();

    /// Called when data is received
    virtual bool onRead() {};
    /// Called when sending data to remote host
    virtual bool onWrite() {};
    /// Called when a connection is first successfully established
    virtual bool onConnect() {};
    /// Called when the socket is disconnected from the client (either forcibly or by the connection dropping)
    virtual bool onDisconnect() {};

    string getRemoteIP();

protected:
    bool _onConnect();
    bool _onDisconnect();
private:
    bool _connected;
    sockaddr_in _client;
};

#endif // SOCKET_H
