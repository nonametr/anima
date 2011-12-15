#ifndef LOGINSERVERHANDLER_H
#define LOGINSERVERHANDLER_H

#include "../shared/socket.h"
#include "../shared/listen_socket.h"
#include "login_server.h"

class ExtShardConnection : public Thread
{
public:
    void run();
    void onShutdown();
    SSWorldThread();
    virtual ~SSWorldThread();
private:
    AtomicBoolean _running;
};

class SSWorld : public Singleton<SSWorld>
{
    friend class SSWorldThread;
public:
    SSWorld(const char* listen_address, uint32 port);
    virtual ~SSWorld();
    void onClientConnectionRead(ClientConnection *pkt);
private:
    void performPacket( ClientConnection *pkt );
    FQueue<ClientConnection*> _data;
};

#define iSSWorld SSWorld::getSingletonPtr()
#endif // LOGINSERVERHANDLER_H