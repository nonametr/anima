#ifndef EXT_CONNECTION_INSTANCE_H
#define EXT_CONNECTION_INSTANCE_H

#include "instance.h"
#include "ext_socket.h"

class ExtSocket;

class ExtSocketInstance : public Instance
{

public:
    ExtSocketInstance(ExtSocket *p_owner);
    virtual ~ExtSocketInstance();
    virtual void handlePacket(Packet* pkt);
private:
    void cSetMoney(Packet* pkt);
    void cSetGold(Packet* pkt);
    void cSetLvl(Packet* pkt);
    void cSetExp(Packet* pkt);
    
    ExtSocket *owner;
    PacketHandler<ExtSocketInstance> _extPacketHandlers[Packets::EG_MAX_ID];
};

#endif // EXT_CONNECTION_INSTANCE_H
