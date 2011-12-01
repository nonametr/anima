#ifndef LOGINSERVERHANDLER_H
#define LOGINSERVERHANDLER_H


#include "../shared/socket.h"
#include "../shared/listensocket.h"

struct Packet
{
    string data;
    Socket *connect;
};

#include "loginserver.h"

class LSWorkerThread;

class LSHandlerSocket : public Socket
{
    friend class LSWorkerThread;
public:
    LSHandlerSocket(SOCKET sock);
    virtual bool onRead( const string &data );
    virtual bool onConnect() {};
    virtual bool onDisconnect() {};
};

class LSWorkerThread : public Thread
{
public:
    void run();
    void onShutdown();
    LSWorkerThread();
    virtual ~LSWorkerThread();
private:
    AtomicBoolean _running;
    FQueue<Packet*> *_data;
};

#endif // LOGINSERVERHANDLER_H
