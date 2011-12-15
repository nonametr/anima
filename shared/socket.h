#ifndef SOCKET_H
#define SOCKET_H

#include "common.h"
#include "socket_base.h"
#include "socket_operations.h"
#include "thread.h"
#include "packet_definitions.h"

#define RECIVE_BUFFER_SIZE 65536

class ListenSocket;

class Socket : public SocketOperations
{
public:
    Socket(int sock)
    {
        ASSERT_CONTINUE(sock > 0);
        _connected.setVal(true);
        _sock = sock;
    }
    Socket();
    virtual ~Socket();

    /// Open a connection to another machine
    void connect(const char * address, uint32 port);
    /// Disconnect the socket
    void disconnect();
    /// Accept from connection
    void accept(sockaddr_in * address);
    /// Send bytes
    void send(const char* out_packet, uint32 size);
    /// Read bytes
    void read();
    
    void setOwner(ListenSocket *owner);
    
    bool isConnected() 
    {
        return _connected.getVal();
    };
    string getRemoteIP();
    inline uint32 getRemotePort() 
    {
        return ntohs(_client.sin_port);
    }
    inline in_addr getRemoteAddress() 
    {
        return _client.sin_addr;
    }
private:
    void _onConnect();
    void _onDisconnect();
    void _onRead(ClientConnection *pkt);
    
    char _recv_buf[RECIVE_BUFFER_SIZE];
    
    ListenSocket *_owner;
    AtomicBoolean _connected;
    sockaddr_in _client;
};

#endif // SOCKET_H
