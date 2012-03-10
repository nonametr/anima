#ifndef SHARD_H
#define SHARD_H

#include "socket.h"
#include "listen_socket.h"
#include "common.h"
#include "game_server.h"
#include "user.h"
#include "instance.h"
#include "main_instance.h"

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
    virtual void onPacketRead(Packet *pkt);
    virtual void onPacketDisconnect(Socket *sock);
    virtual void onPacketConnect(Socket *sock);

    void _performPacket( Packet *pkt );
    FQueue<Packet*> _data;

    MainInstance *_default_instance;
    associative_container< Socket *, shared_ptr<Instance> > _instances;
    AtomicCounter _conn_count;
};
///GameSocket MT
class GameSocketThread : public Thread
{
public:
    virtual void run();
    virtual void onShutdown();
    GameSocketThread(GameSocket *owner);
    virtual ~GameSocketThread();
private:
    GameSocket *shard_owner;
    volatile bool _running;
};

#endif // SHARD_H
