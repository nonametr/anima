#include "shard.h"

initialiseSingleton ( Shard );

Shard::Shard(const char* listen_address, uint32 port) : ListenSocket(listen_address, port)
{
    for (uint32 i = 0; i < iServer->getNumWorkerThreads(); ++i)
    {
        iThreadCore->startThread(new ShardThread);
    }
    for (uint32 i = 0; i < IG_MAX_ID; ++i)
    {
        _shardPacketHandlers[i].status = 0;
        _shardPacketHandlers[i].handler = NULL;
    }
//     _shardPacketHandlers[IG_JOIN].handler = &Shard::cJoin;
}
void Shard::cJoin(ClientConnection* c_pkt)
{
    JoinData join;
    if (sizeof(join) != c_pkt->data_size)
    {
        c_pkt->sock->send(MSG_PACKET_WRONG_DATA_SIZE, strlen(MSG_PACKET_WRONG_DATA_SIZE));
	return;
    }
    memcpy(&join, c_pkt->data, c_pkt->data_size);
    
    
    //TEST DATA 
    int money = 10000;
    OGPacket og_money;
    og_money.type = OG_MONEY;
    og_money.crc32 = 111111111;
    og_money.data = new char[sizeof(money)];
    memcpy(og_money.data, &money, sizeof(money));
    og_money.size = 3*sizeof(int) + sizeof(money);
    
    char buf[og_money.size];
    memcpy(&buf, &og_money, 3*sizeof(int));
    memcpy(&buf[3*sizeof(int)], og_money.data, sizeof(money));
    c_pkt->sock->send(buf, og_money.size);
    
    int gold = 20000;
    OGPacket og_gold;
    og_gold.type = OG_GOLD;
    og_gold.crc32 = 2222222;
    og_gold.data = new char[sizeof(gold)];
    memcpy(og_gold.data, &gold, sizeof(gold));
    og_gold.size = 4*sizeof(int);
    
    char buf_2[og_gold.size];
    memcpy(&buf_2, &og_gold, 3*sizeof(int));
    memcpy(&buf_2[3*sizeof(int)], og_gold.data, sizeof(gold));
    c_pkt->sock->send(buf_2, og_gold.size);
    
    string name = "TEST NAME";
    OGPacket og_name;
    og_name.type = OG_NAME;
    og_name.crc32 = 3333;
    og_name.data = new char[name.length()*sizeof(char)];
    memcpy(og_name.data, name.c_str(), name.length()*sizeof(char));
    og_name.size = 3*sizeof(int) + name.length()*sizeof(char);
    
    char buf_3[og_name.size];
    memcpy(&buf_3, &og_name, 3*sizeof(int));
    memcpy(&buf_3[3*sizeof(int)], og_name.data, name.length()*sizeof(char));
    c_pkt->sock->send(buf_3, og_name.size);
}
void Shard::performPacket( ClientConnection *pkt )
{
//     (this->*_shardPacketHandlers[pkt->type].handler)(pkt);
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

