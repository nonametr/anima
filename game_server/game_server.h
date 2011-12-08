#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "../shared/singleton.h"
#include "../shared/thread.h"
#include "../shared/common.h"
#include "../shared/config.h"
#include "../shared/net_core.h"
#include "../shared/thread_core.h"
#include "../shared/periodic_thread_caller.h"
#include "../shared/version_control.h"

#include <signal.h>

class GameServer : public Singleton<GameServer>
{
public:
    GameServer();
    virtual ~GameServer();
    
    void run();
    void restart()
    {
	_need_restart.SetVal(true);
	stop();
    }
    bool isRestating(){ return _need_restart.GetVal(); }
    void stop() 
    {
        _running.SetVal(false);
    };
private:
    void ininializeObjects();
    void destroyObjects();

    AtomicBoolean _running;
    AtomicBoolean _need_restart;
};

#define iGameServer GameServer::getSingletonPtr()

#endif // GAMESERVER_H
