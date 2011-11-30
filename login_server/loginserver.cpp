#include "loginserver.h"

initialiseSingleton ( LoginServer );

LoginServer::LoginServer()
{
}
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
void LoginServer::ininializeObjects()
{
    new NetCore;
    new ThreadCore;
    new PeriodicThreadCaller;///no need to delete at exit - it's auto runing thread and as all threads its managed by ThreadCore
    
    /// hook signals
    tracelog(OPTIMAL, "Hooking signals...");
    signal(SIGINT, _onSignal);
    signal(SIGTERM, _onSignal);
    signal(SIGABRT, _onSignal);
    signal(SIGHUP, _onSignal);
}
void LoginServer::destroyObjects()
{
    delete iThreadCore;
    delete iConfig;
    delete iNetCore;

    tracelog(OPTIMAL, "Shutting down...");
    signal(SIGINT, 0);
    signal(SIGTERM, 0);
    signal(SIGABRT, 0);
    signal(SIGHUP, 0);
}
LoginServer::~LoginServer()
{

}
void LoginServer::run()
{
    ininializeObjects();

    /** write pid file */
    FILE* fPid = fopen("login_server.pid", "w");
    if (fPid)
    {
        uint pid;
        pid = getpid();
        fprintf(fPid, "%u", (unsigned int)pid);
        fclose(fPid);
    }
    
    tracelog(OPTIMAL, "Success! Ready for connections");

    ///entering infinity loop state
    while (_running.GetVal())
    {
        sleep(1);
    }
    destroyObjects();
}

