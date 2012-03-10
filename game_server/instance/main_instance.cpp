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
void MainInstance::cJoin(Packet* pkt)
{
    shared_ptr<CInt64> join_data = CInt64::decompress(pkt);
    if (join_data == shared_ptr<CInt64>())
        return;

    uint32 uid = join_data->uid;
    
    shared_ptr<User> user = iStorage->getLocalUser(uid);
    
    Packet ret_pkt = CInt32::create(uid, 1, OG_MSG);
    pkt->sock->send(&ret_pkt);
}
