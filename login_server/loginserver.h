#ifndef LOGINSERVER_H
#define LOGINSERVER_H
#include "../shared/singleton.h"
#include "../shared/thread.h"
#include "../shared/common.h"
#include "../shared/config.h"
#include "../shared/netcore.h"
#include "../shared/threadcore.h"
#include "../shared/periodicthreadcaller.h"

#include <signal.h>

class LoginServer : public Singleton<LoginServer>
{
public:
    LoginServer();
    virtual ~LoginServer();
    void run();
    void stop() { _running.SetVal(false); };
private:
  void ininializeObjects();
  void destroyObjects();
  
  AtomicBoolean _running;
};

#define iLoginServer LoginServer::getSingletonPtr()

#endif // LOGINSERVER_H
