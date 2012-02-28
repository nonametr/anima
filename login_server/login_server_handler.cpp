#include "login_server_handler.h"
#include "server.h"

initialiseSingleton ( LSWorld );

LSWorld::LSWorld(const char* listen_address, uint32 port) : ListenSocket(listen_address, port)
{
    uint32 num_threads = iServer->getNumWorkerThreads();
    for (uint32 i = 0; i < num_threads; ++i)
    {
        iThreadCore->startThread(new LSWorldThread);
    }
}
void LSWorld::performPacket( Packet *pkt )
{
//   pkt->connect->send("hello");
}
LSWorld::~LSWorld()
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
void LSWorldThread::run()
{
    Packet* pkt = NULL;
    while (_running.getVal())
    {
        if (pkt != NULL)
        {
            iLSWorld->performPacket( pkt );
            delete pkt;
        }

        pkt = iLSWorld->_data.pop( );
        if (pkt == NULL)
            sleep(1);
    }
}
void LSWorldThread::onShutdown()
{
    _running.setVal(false);
}
LSWorldThread::LSWorldThread()
{
    _running.setVal(true);
}
LSWorldThread::~LSWorldThread()
{
}
