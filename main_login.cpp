#include <iostream>
#include "./shared/common.h"
#include "./shared/config.h"
#include "./shared/netcore.h"
#include "./shared/threadcore.h"
#include "./shared/periodicthreadcaller.h"

bool ininializeSingletons()
{
    new Config;
    new NetCore;
    new ThreadCore;
    new PeriodicThreadCaller;
}
class TST : public Thread
{
public:
  void run(){ traceerr("YOYO"); };
  void onShutdown(){};
};
int main ( int argc, char **argv )
{
     ininializeSingletons();
     tracelog(4, "dasd %u", 213);
     TST *aaa = new TST();
     //iThreadCore->startThread(aaa);
     iPeriodicThreadCaller->startPeriodicThread(aaa, 5);
     std::cout << "Hello, world! TEST GIT" << std::endl;
     sleep(2);
    delete iThreadCore;
    delete iConfig;
    delete iNetCore;
    return 1;
}
