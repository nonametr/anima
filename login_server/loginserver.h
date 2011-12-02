#ifndef LOGINSERVER_H
#define LOGINSERVER_H
#include "../shared/singleton.h"
#include "../shared/thread.h"
#include "../shared/common.h"
#include "../shared/config.h"
#include "../shared/netcore.h"
#include "../shared/threadcore.h"
#include "../shared/periodicthreadcaller.h"
#include "../shared/version_control.h"

#include "loginserverhandler.h"

#include <signal.h>

class LoginServer : public Singleton<LoginServer>
{
    friend class LSHandlerSocket;
    friend class LSWorkerThread;
public:
    LoginServer();
    virtual ~LoginServer();
    
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
    void performPacket(Packet *pkt);
    void ininializeObjects();
    void destroyObjects();

    AtomicBoolean _running;
    AtomicBoolean _need_restart;

    FQueue<Packet*> *getQueuePtr()
    {
        return &_data;
    }
    FQueue<Packet*> _data;
};

#define iLoginServer LoginServer::getSingletonPtr()

#endif // LOGINSERVER_H
