#include "loginserverhandler.h"

LSHandlerSocket::LSHandlerSocket(SOCKET sock) : Socket(sock)
{
    uint num_threads = iConfig->getParam(Config::LS_NUM_LOGIN_PROCCESSING_THREADS);
    for (uint i = 0; i < num_threads; ++i)
    {
        iThreadCore->startThread(new LSWorkerThread);
    }
}
bool LSHandlerSocket::onRead( const string &data )
{
    Packet *rcv_pack = new Packet;
    rcv_pack->connect = this;
    rcv_pack->data = data;

    iLoginServer->getQueuePtr()->push(rcv_pack);
}
void LSWorkerThread::run()
{
    Packet* pkt = NULL;
    while (_running.GetVal())
    {
        if (pkt != NULL)
        {
            iLoginServer->performPacket( pkt );
            delete pkt;
        }

        pkt = _data->pop( );
        if (pkt == NULL)
            sleep(1);
    }
}
void LSWorkerThread::onShutdown()
{
    _running.SetVal(false);
}
LSWorkerThread::LSWorkerThread()
{
    _data = iLoginServer->getQueuePtr();
    _running.SetVal(true);
}
LSWorkerThread::~LSWorkerThread()
{
}
