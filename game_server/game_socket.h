#ifndef SHARD_H
#define SHARD_H

#include "../shared/net/socket.h"
#include "../shared/net/listen_socket.h"
#include "../shared/common.h"
#include "game_server.h"
#include "./user/user.h"
#include "./instance/instance.h"
#include "./instance/main_instance.h"

class MainInstance;

///Local shard soket
class GameSocket : public ListenSocket
{
    friend class GameSocketThread;
public:
    GameSocket(const char* listen_address, uint32 port);
    virtual ~GameSocket();
    void changeInstance(Socket *owner, shared_ptr<Instance> new_instance);
private:
    ClientPacket* _createClientPacket(Packet *pkt);
    virtual void onClientPacketRead(Packet *pkt);
    virtual void onClientPacketDisconnect(Socket *sock);
    virtual void onClientPacketConnect(Socket *sock);

    void _performClientPacket( ClientPacket *pkt );
    FQueue<ClientPacket*> _data;

    MainInstance *_default_instance;
    associative_container< Socket *, shared_ptr<Instance> > _instances;
    AtomicCounter _conn_count;
};
///ClientPacket MT
class GameSocketThread : public Thread
{
public:
    virtual void run();
    virtual void onShutdown();
    GameSocketThread(GameSocket *owner);
    virtual ~GameSocketThread();
private:
    GameSocket *shard_owner;
    AtomicBoolean _running;
};

#endif // SHARD_H
