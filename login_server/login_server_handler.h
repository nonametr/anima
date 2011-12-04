#ifndef LOGINSERVERHANDLER_H
#define LOGINSERVERHANDLER_H


#include "../shared/socket.h"
#include "../shared/listen_socket.h"
#include "login_server.h"

struct Packet
{
    string data;
    Socket *connect;
};

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
    LSWorld(const char* listen_address, uint port);
    virtual ~LSWorld();
    void onClientRead(const string &data);
private:
    void performPacket( Packet *pkt );
    FQueue<Packet*> _data;
};

#define iLSWorld LSWorld::getSingletonPtr()
#endif // LOGINSERVERHANDLER_H
