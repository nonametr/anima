#ifndef DEBUG_UPDATE_H
#define DEBUG_UPDATE_H
#include "thread.h"
#include "login_socket.h"

class DebugUpdate : public Thread
{

public:
    DebugUpdate(LoginSocket *ls);
    virtual ~DebugUpdate();
    virtual void run();
    virtual void onShutdown();
private:
    volatile bool _running;
    LoginSocket *_ls;
};

#endif // DEBUG_UPDATE_H
