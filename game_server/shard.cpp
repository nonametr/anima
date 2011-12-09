#include "shard.h"

initialiseSingleton ( Shard );

Shard::Shard(const char* listen_address, uint port) : ListenSocket(listen_address, port)
{
    uint num_threads = iConfig->getParam(Config::GS_NUM_PROCCESSING_THREADS);
    for (uint i = 0; i < num_threads; ++i)
    {
        iThreadCore->startThread(new ShardThread);
    }
}
void Shard::onClientRead(Client *pkt)
{
    _data.push(pkt);
}
void Shard::performPacket( Client *pkt )
{
    char buf[1024];
    snprintf(buf, 1024, "echo = %s", pkt->data);
    tracelog(4, "%s", buf);
    pkt->connection->send(buf, strlen(buf));
}
Shard::~Shard()
{
    while (true)
    {
        Client *pkt = _data.pop();
        if (pkt)
            delete pkt;
        else
            break;
        tracelog(OPTIMAL, "Clearing request queue... %u req. left", _data.get_size());
    }
}
void ShardThread::run()
{
    Client* pkt = NULL;
    while (_running.GetVal())
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
    _running.SetVal(false);
}
ShardThread::ShardThread()
{
    _running.SetVal(true);
}
ShardThread::~ShardThread()
{
}

