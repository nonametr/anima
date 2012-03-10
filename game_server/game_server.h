#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "singleton.h"
#include "thread.h"
#include "common.h"
#include "config.h"
#include "net_core.h"
#include "thread_core.h"
#include "periodic_thread_caller.h"
#include "version_control.h"
#include "common.h"

#include <signal.h>

#include "game_socket.h"
#include "server.h"

class GameServer : public Server
{
public:
    GameServer();
    virtual ~GameServer();

    void run();
private:
    void ininializeObjects();
    void destroyObjects();
    
    Socket *_gs, *_ls, *_es;
};

#endif // GAMESERVER_H
