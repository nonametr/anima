#ifndef SHARD_H
#define SHARD_H

#include "../shared/socket.h"
#include "../shared/listen_socket.h"
#include "game_server.h"

class ShardThread : public Thread
{
public:
    void run();
    void onShutdown();
    ShardThread();
    virtual ~ShardThread();
private:
    AtomicBoolean _running;
};

class Shard : public ListenSocket, public Singleton<Shard>
{
    friend class ShardThread;
public:
    Shard(const char* listen_address, uint port);
    virtual ~Shard();
    void onClientRead(Client *pkt);
private:
    void performPacket( Client *pkt );
    FQueue<Client*> _data;
};

#define iShard Shard::getSingletonPtr()

#endif // SHARD_H
