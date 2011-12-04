#include "login_server_handler.h"

initialiseSingleton ( LSWorld );

LSWorld::LSWorld(const char* listen_address, uint port) : ListenSocket(listen_address, port)
{
    uint num_threads = iConfig->getParam(Config::LS_NUM_LOGIN_PROCCESSING_THREADS);
    for (uint i = 0; i < num_threads; ++i)
    {
        iThreadCore->startThread(new LSWorldThread);
    }
}
void LSWorld::onClientRead(const string &data)
{
    Packet *rcv_pack = new Packet;
    rcv_pack->connect = this;
    rcv_pack->data = data;

    _data.push(rcv_pack);
}
void LSWorld::performPacket( Packet *pkt )
{
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
    while (_running.GetVal())
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
    _running.SetVal(false);
}
LSWorldThread::LSWorldThread()
{
    _running.SetVal(true);
}
LSWorldThread::~LSWorldThread()
{
}
