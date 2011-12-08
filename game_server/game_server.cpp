#include "game_server.h"
#include "shard.h"

initialiseSingleton ( GameServer );

GameServer::GameServer()
{
    _running.SetVal(true);
    _need_restart.SetVal(false);
}
/*** Signal Handler ***/
void _onSignal(int s)
{
    switch (s)
    {
    case SIGHUP:
    {
        tracelog(OPTIMAL, "Received SIGHUP signal, reloading login server.");
        iGameServer->restart();
    }
    break;
    case SIGINT:
    case SIGTERM:
    case SIGABRT:
        iGameServer->stop();
        break;
    }

    signal(s, _onSignal);
}
void GameServer::ininializeObjects()
{
    new ThreadCore;
    new NetCore;
    new VersionControl;
    new PeriodicThreadCaller;///no need to delete at exit - it's auto runing thread and as all threads its managed by ThreadCore

    /// hook signals
    tracelog(OPTIMAL, "Hooking signals...");
    signal(SIGINT, _onSignal);
    signal(SIGTERM, _onSignal);
    signal(SIGABRT, _onSignal);
    signal(SIGHUP, _onSignal);
}
void GameServer::destroyObjects()
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
GameServer::~GameServer()
{
}
void GameServer::run()
{
    ininializeObjects();

    /** write pid file */
    FILE* fPid = fopen("login_server.pid", "w");
    if (fPid)
    {
        uint pid;
        pid = getpid();
        fprintf(fPid, "%u", (uint)pid);
        fclose(fPid);
    }

    uint listen_port = iConfig->getParam(Config::GS_PORT);
    string listen_ip = iConfig->getParam(Config::GS_IP);

    new Shard(listen_ip.c_str(), listen_port);
    
    tracelog(OPTIMAL, "Server version: %s. Almost started...", iVersionControl->getVersion().c_str());
    tracelog(OPTIMAL, "Success! Ready for connections");

     ///entering infinity loop state
     while (_running.GetVal())
     {
        ///Some periodic checks possible here
        sleep(10);
     }
    destroyObjects();
}
