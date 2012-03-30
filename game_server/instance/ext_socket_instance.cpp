#include "ext_socket_instance.h"

ExtSocketInstance::ExtSocketInstance(ExtSocket *p_owner) : owner(p_owner)
{
    for (uint32 i = 0; i < Packets::EG_MAX_ID; ++i)
    {
        _extPacketHandlers[i].setHandler(PacketHandler<ExtSocketInstance>::NO_HANDLER_SET, NULL);
    }
    _extPacketHandlers[Packets::EG_SET_MONEY].setHandler(PacketHandler<ExtSocketInstance>::HANDLER_SET, &ExtSocketInstance::cSetMoney);
    _extPacketHandlers[Packets::EG_SET_GOLD].setHandler(PacketHandler<ExtSocketInstance>::HANDLER_SET, &ExtSocketInstance::cSetGold);
    _extPacketHandlers[Packets::EG_SET_EXP].setHandler(PacketHandler<ExtSocketInstance>::HANDLER_SET, &ExtSocketInstance::cSetExp);
    _extPacketHandlers[Packets::EG_SET_LVL].setHandler(PacketHandler<ExtSocketInstance>::HANDLER_SET, &ExtSocketInstance::cSetLvl);
}
ExtSocketInstance::~ExtSocketInstance()
{

}
void ExtSocketInstance::handlePacket(Packet* pkt)
{
    if (_extPacketHandlers[pkt->type].status == PacketHandler<ExtSocketInstance>::NO_HANDLER_SET)
    {
	Packet send_pkt = OG_STR::create(0, MSG_PACKET_WRONG_ID_IN_THIS_INSTANCE);
	pkt->sock->send(&send_pkt);
        return;
    }
    (this->*_extPacketHandlers[pkt->type].handler)(pkt);
}
void ExtSocketInstance::cSetMoney(Packet* pkt)
{
    CInt32 cMoney;
    if (sizeof(cMoney) != pkt->data_size)
    {
	Packet send_pkt = OG_STR::create(0, MSG_PACKET_WRONG_DATA_SIZE);
	pkt->sock->send(&send_pkt);
        return;
    }
    memcpy(&cMoney, &pkt->data[0], pkt->data_size);
}
void ExtSocketInstance::cSetGold(Packet* pkt)
{
}
void ExtSocketInstance::cSetLvl(Packet* pkt)
{
}
void ExtSocketInstance::cSetExp(Packet* pkt)
{
}
