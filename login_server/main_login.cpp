#include <iostream>
#include <signal.h>
#include <sys/resource.h>

#include "loginserver.h"

/*** Signal Handler ***/
void _onSignal(int s)
{
    switch (s)
    {
    case SIGHUP:
    {
        tracelog(OPTIMAL, "Received SIGHUP signal, reloading login server.");
        //THERE WILL BE RELOADING SERVER CODE
    }
    break;
    case SIGINT:
    case SIGTERM:
    case SIGABRT:
        iLoginServer->stop();
        break;
    }

    signal(s, _onSignal);
}
int main ( int argc, char **argv )
{
    new Config;
    iConfig->loadFromFile();///it will use default path to configuration file
    
    tracelog(OPTIMAL, "Starting login server");

    rlimit rl;
    if (getrlimit(RLIMIT_CORE, &rl) == -1)
    {
        traceerr("Getrlimit failed. This could be problem.\n");
    }
    else
    {
        rl.rlim_cur = rl.rlim_max;
        if (setrlimit(RLIMIT_CORE, &rl) == -1)
            traceerr("Setrlimit failed. Server may not save core.dump files.\n");
    }
    
    /// hook signals
    tracelog(OPTIMAL, "Hooking signals...");
    signal(SIGINT, _onSignal);
    signal(SIGTERM, _onSignal);
    signal(SIGABRT, _onSignal);
    signal(SIGHUP, _onSignal);
    
    new LoginServer;
    iLoginServer->run();
    
    delete iLoginServer;
    delete iConfig;
    
    return EXIT_SUCCESS;
}
