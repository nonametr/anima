#include "game_server.h"
#include "game_socket.h"
#include "login_socket.h"
#include "ext_socket.h"
#include "dict_manager.h"
#include "random.h"

GameServer::GameServer()
{
    _running = true;
    _need_restart.setVal ( false );
}
/*** Signal Handler ***/
void _onGSSignal ( int s )
{
    switch ( s )
    {
    case SIGHUP:
    {
        tracelog ( OPTIMAL, "Received SIGHUP signal, reloading login server." );
        iServer->restart();
    }
    break;
    case SIGINT:
    case SIGTERM:
    case SIGABRT:
        iServer->stop();
        break;
    }

    signal ( s, _onGSSignal );
}
void GameServer::ininializeObjects()
{
    new Random;
    new NetCore;
    new VersionControl;
    new PeriodicThreadCaller;///no need to delete at exit - it's auto runing thread and as all threads its managed by ThreadCore
    new Storage;
    new DictManager;

    /// hook signals
    tracelog ( OPTIMAL, "Hooking signals..." );
    signal ( SIGINT, _onGSSignal );
    signal ( SIGTERM, _onGSSignal );
    signal ( SIGABRT, _onGSSignal );
    signal ( SIGHUP, _onGSSignal );
}
void GameServer::destroyObjects()
{
    tracelog ( OPTIMAL, "Shutting down..." );
    delete iRandom;
    delete iVersionControl;
    delete iStorage;
    delete iDictManager;
//     delete iNetCore;
    signal ( SIGINT, 0 );
    signal ( SIGTERM, 0 );
    signal ( SIGABRT, 0 );
    signal ( SIGHUP, 0 );
}
GameServer::~GameServer()
{
    delete _gs;
    delete _ls;
    delete _es;
}
void GameServer::run()
{
    ininializeObjects();

    ///No need to terminate it manualy, it'll be terminated automaticly by NetCore
    _gs = new GameSocket ( _listen_ip.c_str(), _port );
    _gs->setType(Socket::DEFAULT_SOCKET);
    _ls = new LoginSocket ( _listen_ip.c_str(), _http_port );
    _ls->setType(Socket::HTTP_SOCKET);
    _es = new ExtSocket ( _listen_ip.c_str(), _ext_port );
    _es->setType(Socket::DEFAULT_SOCKET);

    tracelog ( OPTIMAL, "Server version: %s. Almost started...", iVersionControl->getVersion().c_str() );
    tracelog ( OPTIMAL, "Success! Ready for connections" );

    ///entering infinity loop state
    while ( _running )
    {
        ///Some periodic checks possible here
        sleep ( 25 );
//         break;
    }

    destroyObjects();
}
