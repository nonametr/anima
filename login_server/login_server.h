#ifndef LOGINSERVER_H
#define LOGINSERVER_H
#include "singleton.h"
#include "thread.h"
#include "common.h"
#include "config.h"
#include "net_core.h"
#include "thread_core.h"
#include "periodic_thread_caller.h"
#include "version_control.h"

#include "login_server_handler.h"

#include <signal.h>
#include "server.h"

class LoginServer : public Server
{
public:
    LoginServer();
    virtual ~LoginServer();
    
    void run();
private:
    void ininializeObjects();
    void destroyObjects();
};

#endif // LOGINSERVER_H
