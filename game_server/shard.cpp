#include "shard.h"

initialiseSingleton ( Shard );

Shard::Shard(const char* listen_address, uint32 port) : ListenSocket(listen_address, port)
{
    uint32 num_threads = iConfig->getParam(Config::GS_NUM_PROCCESSING_THREADS);
    for (uint32 i = 0; i < num_threads; ++i)
    {
        iThreadCore->startThread(new ShardThread);
    }
    
    
}
void Shard::onClientConnectionRead(ClientConnection *pkt)
{
    _data.push(pkt);
}
void Shard::performPacket( ClientConnection *pkt )
{
//     char buf[1024];
//     PacketEcho tst;
//     memcpy(&tst, pkt->data, pkt->size);
//     snprintf(buf, 1024, "echo = %s", tst.data);
//     tracelog(4, "%s", buf);
//     pkt->connection->send(buf, strlen(buf));
}
Shard::~Shard()
{
    while (true)
    {
        ClientConnection *pkt = _data.pop();
        if (pkt)
            delete pkt;
        else
            break;
        tracelog(OPTIMAL, "Clearing request queue... %u req. left", _data.get_size());
    }
}
void ShardThread::run()
{
    ClientConnection* pkt = NULL;
    while (_running.getVal())
    {
        if (pkt != NULL)
        {
            iShard->performPacket( pkt );
            delete pkt;
        }

        pkt = iShard->_data.pop( );
        if (pkt == NULL)
            sleep(1);
    }
}
void ShardThread::onShutdown()
{
    _running.setVal(false);
}
ShardThread::ShardThread()
{
    _running.setVal(true);
}
ShardThread::~ShardThread()
{
}

