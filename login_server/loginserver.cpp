#include "loginserver.h"

initialiseSingleton ( LoginServer );

LoginServer::LoginServer()
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
        iLoginServer->restart();
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
    while (true)
    {
        Packet *pkt = _data.pop();
        if (pkt)
            delete pkt;
        else
            break;
        tracelog(OPTIMAL, "Clearing request queue... %u req. left", _data.get_size());
    }
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
        fprintf(fPid, "%u", (uint)pid);
        fclose(fPid);
    }

    uint listen_port = iConfig->getParam(Config::LS_PORT);
    string listen_ip = iConfig->getParam(Config::LS_IP);

    new ListenSocket<LSHandlerSocket>(listen_ip.c_str(), listen_port);

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
void LoginServer::performPacket(Packet *pkt)
{
    tracelog(OPTIMAL, "performPacket = %s", pkt->data.c_str());
    pkt->connect->send("recved and processed");
    pkt->connect->disconnect();
}

