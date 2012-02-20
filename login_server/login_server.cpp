#include "login_server.h"

LoginServer::LoginServer()
{
    _running.setVal(true);
    _need_restart.setVal(false);
}
/*** Signal Handler ***/
void _onLSSignal(int s)
{
    switch (s)
    {
    case SIGHUP:
    {
        tracelog(OPTIMAL, "Received SIGHUP signal, reloading login server.");
        iServer->restart();
    }
    break;
    case SIGINT:
    case SIGTERM:
    case SIGABRT:
        iServer->stop();
        break;
    }

    signal(s, _onLSSignal);
}
void LoginServer::ininializeObjects()
{
    new ThreadCore;
    new NetCore;
    new VersionControl;
    new PeriodicThreadCaller;///no need to delete at exit - it's auto runing thread and as all threads its managed by ThreadCore

    /// hook signals
    tracelog(OPTIMAL, "Hooking signals...");
    signal(SIGINT, _onLSSignal);
    signal(SIGTERM, _onLSSignal);
    signal(SIGABRT, _onLSSignal);
    signal(SIGHUP, _onLSSignal);
}
void LoginServer::destroyObjects()
{
    tracelog(OPTIMAL, "Shutting down...");
    delete iThreadCore;
    delete iNetCore;
    delete iVersionControl;

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
        uint32 pid;
        pid = getpid();
        fprintf(fPid, "%u", (uint32)pid);
        fclose(fPid);
    }

    new LSWorld(_listen_ip.c_str(), _port);

    tracelog(OPTIMAL, "Server version: %s. Almost started...", iVersionControl->getVersion().c_str());
    tracelog(OPTIMAL, "Success! Ready for connections");

    ///entering infinity loop state
//      while (_running.GetVal())
//      {
        ///Some periodic checks possible here
        sleep(10);
//      }
    destroyObjects();
}

