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
    void cJoin(Packet* pkt);

    GameSocket *owner_shard;
    PacketHandler<MainInstance> _shardPacketHandlers[IG_MAX_ID];
};

#endif // MAIN_INST_H
