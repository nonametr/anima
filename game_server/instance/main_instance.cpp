#include "main_instance.h"
#include "common.h"

MainInstance::MainInstance(GameSocket *owner) : owner_shard(owner)
{
    for (uint32 i = 0; i < Packets::IG_JOIN; ++i)
    {
        _shardPacketHandlers[i].setHandler(PacketHandler<MainInstance>::NO_HANDLER_SET, NULL);
    }
    _shardPacketHandlers[Packets::IG_JOIN].setHandler(PacketHandler<MainInstance>::HANDLER_SET, &MainInstance::cJoin);
}

void MainInstance::handlePacket(Packet* pkt)
{
    if (_shardPacketHandlers[pkt->type].status == PacketHandler<MainInstance>::NO_HANDLER_SET)
    {
        Packet send_pkt = OG_STR::create(0, MSG_PACKET_WRONG_ID_IN_THIS_INSTANCE);
        pkt->sock->send(&send_pkt);
        return;
    }
    (this->*_shardPacketHandlers[pkt->type].handler)(pkt);
}
void MainInstance::cJoin(Packet* pkt)
{
    shared_ptr<IG_JOIN> join_data = IG_JOIN::decompress(pkt);
    if (join_data == shared_ptr<IG_JOIN>())
        return;

    shared_ptr<User> usr = iStorage->getOnlineUser(pkt->sock->getSockDescriptor());
    if (usr == shared_ptr<User>())
    {
        shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->query("SELECT uid FROM logins WHERE social_id = %llu", join_data->soc_id));
        if (!qres.get())
        {
            traceerr("%s", "No user found!");
            return;
        }
        Field *field = qres->fetch();
        int uid = field[0].getUInt32();
        usr = iStorage->getLocalUser(uid);
        iStorage->addOnlineUser(pkt->sock->getSockDescriptor(), usr);
    }
    usr->join(pkt->sock);
    usr->updateClient();
}
