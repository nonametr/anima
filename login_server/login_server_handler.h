#ifndef LOGINSERVERHANDLER_H
#define LOGINSERVERHANDLER_H

#include "socket.h"
#include "listen_socket.h"
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
    void onPacketRead(Packet *pkt) 
    {
	//Packet *pkt = Packetize(pkt_data, bytes_recv, sock);
        //_data.push(pkt);
    }
    void onPacketDisconnect(Socket *sock) {
        --_conn_count;
    };
    void onPacketConnect(Socket *sock) {
        ++_conn_count;
    };

    void performPacket( Packet *pkt );
    FQueue<Packet*> _data;
    AtomicCounter _conn_count;
};

#define iLSWorld LSWorld::getSingletonPtr()
#endif // LOGINSERVERHANDLER_H
