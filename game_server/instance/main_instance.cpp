#include "main_instance.h"

MainInstance::MainInstance(GameSocket *owner) : owner_shard(owner)
{
    for (uint32 i = 0; i < IG_MAIN_JOIN; ++i)
    {
        _shardPacketHandlers[i].setHandler(PacketHandler<MainInstance>::NO_HANDLER_SET, NULL);
    }
    _shardPacketHandlers[IG_MAIN_JOIN].setHandler(PacketHandler<MainInstance>::HANDLER_SET, &MainInstance::cJoin);
}

void MainInstance::handlePacket(Packet* pkt)
{
    if (_shardPacketHandlers[pkt->type].status == PacketHandler<MainInstance>::NO_HANDLER_SET)
    {
        pkt->sock->send(MSG_PACKET_WRONG_ID_IN_THIS_INSTANCE, strlen(MSG_PACKET_WRONG_ID_IN_THIS_INSTANCE));
        return;
    }
    (this->*_shardPacketHandlers[pkt->type].handler)(pkt);
}

void MainInstance::cJoin(Packet* c_pkt)
{
//     JoinData join;
//     if (sizeof(join) != c_pkt->data_size)
//     {
//         c_pkt->sock->send(MSG_PACKET_WRONG_DATA_SIZE, strlen(MSG_PACKET_WRONG_DATA_SIZE));
//         return;
//     }
//     memcpy(&join, c_pkt->data, c_pkt->data_size);
// 
//     //TEST DATA
//     int money = 10000;
//     OGPacket og_money;
//     og_money.type = OG_MONEY;
//     og_money.crc32 = 111111111;
//     og_money.data = new char[sizeof(money)];
//     memcpy(og_money.data, &money, sizeof(money));
//     og_money.size = 3*sizeof(int) + sizeof(money);
// 
//     char buf[og_money.size];
//     memcpy(&buf, &og_money, 3*sizeof(int));
//     memcpy(&buf[3*sizeof(int)], og_money.data, sizeof(money));
//     c_pkt->sock->send(buf, og_money.size);
// 
//     int gold = 20000;
//     OGPacket og_gold;
//     og_gold.type = OG_GOLD;
//     og_gold.crc32 = 2222222;
//     og_gold.data = new char[sizeof(gold)];
//     memcpy(og_gold.data, &gold, sizeof(gold));
//     og_gold.size = 4*sizeof(int);
// 
//     char buf_2[og_gold.size];
//     memcpy(&buf_2, &og_gold, 3*sizeof(int));
//     memcpy(&buf_2[3*sizeof(int)], og_gold.data, sizeof(gold));
//     c_pkt->sock->send(buf_2, og_gold.size);
// 
//     string name = "TEST NAME";
//     OGPacket og_name;
//     og_name.type = OG_NAME;
//     og_name.crc32 = 3333;
//     og_name.data = new char[name.length()*sizeof(char)];
//     memcpy(og_name.data, name.c_str(), name.length()*sizeof(char));
//     og_name.size = 3*sizeof(int) + name.length()*sizeof(char);
// 
//     char buf_3[og_name.size];
//     memcpy(&buf_3, &og_name, 3*sizeof(int));
//     memcpy(&buf_3[3*sizeof(int)], og_name.data, name.length()*sizeof(char));
//     c_pkt->sock->send(buf_3, og_name.size);
}