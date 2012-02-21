#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "../shared/singleton.h"
#include "../shared/mt/thread.h"
#include "../shared/common.h"
#include "../shared/config.h"
#include "../shared/net/net_core.h"
#include "../shared/mt/thread_core.h"
#include "../shared/mt/periodic_thread_caller.h"
#include "../shared/version_control.h"
#include "../shared/common.h"

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
};

#endif // GAMESERVER_H
