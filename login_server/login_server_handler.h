#ifndef LOGINSERVERHANDLER_H
#define LOGINSERVERHANDLER_H

#include "../shared/net/socket.h"
#include "../shared/net/listen_socket.h"
#include "login_server.h"

class LSWorldThread : public Thread
{
public:
    void run();
    void onShutdown();
    LSWorldThread();
    virtual ~LSWorldThread();
private:
    AtomicBoolean _running;
};

class LSWorld : public ListenSocket, public Singleton<LSWorld>
{
    friend class LSWorldThread;
public:
    LSWorld(const char* listen_address, uint32 port);
    virtual ~LSWorld();
private:
    void onClientConnectionRead(char *pkt_data, int bytes_recv, Socket *sock) 
    {
	ClientConnection *pkt = paketize(pkt_data, bytes_recv, sock);
        _data.push(pkt);
    }
    void onClientConnectionDisconnect(Socket *sock) {
        --_conn_count;
    };
    void onClientConnectionConnect(Socket *sock) {
        ++_conn_count;
    };

    void performPacket( ClientConnection *pkt );
    FQueue<ClientConnection*> _data;
    AtomicCounter _conn_count;
};

#define iLSWorld LSWorld::getSingletonPtr()
#endif // LOGINSERVERHANDLER_H
