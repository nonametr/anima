#ifndef LOGINSERVERHANDLER_H
#define LOGINSERVERHANDLER_H

#include "../shared/socket.h"
#include "../shared/listen_socket.h"
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
    void onClientConnectionRead(ClientConnection *pkt);
private:
    void performPacket( ClientConnection *pkt );
    FQueue<ClientConnection*> _data;
};

#define iLSWorld LSWorld::getSingletonPtr()
#endif // LOGINSERVERHANDLER_H
