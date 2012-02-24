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
    void onClientPacketRead(Packet *pkt) 
    {
	//ClientPacket *pkt = paketize(pkt_data, bytes_recv, sock);
        //_data.push(pkt);
    }
    void onClientPacketDisconnect(Socket *sock) {
        --_conn_count;
    };
    void onClientPacketConnect(Socket *sock) {
        ++_conn_count;
    };

    void performPacket( ClientPacket *pkt );
    FQueue<ClientPacket*> _data;
    AtomicCounter _conn_count;
};

#define iLSWorld LSWorld::getSingletonPtr()
#endif // LOGINSERVERHANDLER_H
