#ifndef MAIN_INST_H
#define MAIN_INST_H

#include "instance.h"
#include "../game_socket.h"

class GameSocket;

class MainInstance : public Instance
{
public:
    MainInstance(GameSocket *owner);
    virtual void handlePaket(ClientConnection* pkt);
private:
    void cJoin(ClientConnection* pkt);

    GameSocket *owner_shard;
    PaketHandler<MainInstance> _shardPacketHandlers[IG_MAX_ID];
};

#endif // MAIN_INST_H
