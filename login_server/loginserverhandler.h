#ifndef LOGINSERVERHANDLER_H
#define LOGINSERVERHANDLER_H


#include "../shared/socket.h"
#include "../shared/listensocket.h"

class LoginServerHandler : public Socket
{
public:
    virtual bool onRead() {};
    virtual bool onConnect() {};
    virtual bool onDisconnect() {};
private:
};

#endif // LOGINSERVERHANDLER_H
