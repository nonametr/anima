#include "game_server.h"
#include "game_socket.h"

GameServer::GameServer()
{
    _running.setVal(true);
    _need_restart.setVal(false);
}
/*** Signal Handler ***/
void _onGSSignal(int s)
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

    signal(s, _onGSSignal);
}
void GameServer::ininializeObjects()
{
    new NetCore;
    new VersionControl;
    new PeriodicThreadCaller;///no need to delete at exit - it's auto runing thread and as all threads its managed by ThreadCore

    /// hook signals
    tracelog(OPTIMAL, "Hooking signals...");
    signal(SIGINT, _onGSSignal);
    signal(SIGTERM, _onGSSignal);
    signal(SIGABRT, _onGSSignal);
    signal(SIGHUP, _onGSSignal);
}
void GameServer::destroyObjects()
{
    tracelog(OPTIMAL, "Shutting down...");
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

    ///No need to terminate it manualy, it'll be terminated automaticly by NetCore
    new GameSocket(_listen_ip.c_str(), _port);
    
    tracelog(OPTIMAL, "Server version: %s. Almost started...", iVersionControl->getVersion().c_str());
    tracelog(OPTIMAL, "Success! Ready for connections");

     ///entering infinity loop state
     while (_running.getVal())
     {
        ///Some periodic checks possible here
        sleep(10);
     }
    destroyObjects();
}
