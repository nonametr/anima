#ifndef MAIN_INST_H
#define MAIN_INST_H

#include "instance.h"
#include "game_socket.h"
#include "storage.h"

class GameSocket;

class MainInstance : public Instance
{
public:
    MainInstance(GameSocket *owner);
    virtual void handlePacket(Packet* pkt);
private:
    User* getUser(Packet* pkt);
    void cJoin(User* usr, Packet* pkt);
    void cGetLocationsInfo(User* usr, Packet* pkt);
    void cStartLocation(User* usr, Packet* pkt);
    void cFinishLocation(User* usr, Packet* pkt);
    void cKickBoss(User* usr, Packet* pkt);
    void cGetBossUpdate(User* usr, Packet* pkt);
    void cExchange(User* usr, Packet* pkt);
    void cReqColl(User* usr, Packet* pkt);

    GameSocket *owner_shard;
    PacketHandler<MainInstance> _shardPacketHandlers[Packets::IG_MAX_ID];
};

#endif // MAIN_INST_H
