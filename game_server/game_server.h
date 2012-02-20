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

#include "shard.h"
#include "server.h"

class GameServer : public Server
{
public:
    GameServer();
    virtual ~GameServer();

    void run();
    void restart()
    {
        _need_restart.setVal(true);
        stop();
    }
    bool isRestating() {
        return _need_restart.getVal();
    }
    void stop()
    {
        _running.setVal(false);
    };
private:
    void ininializeObjects();
    void destroyObjects();

    AtomicBoolean _running;
    AtomicBoolean _need_restart;
};

#endif // GAMESERVER_H
