#ifndef SHARD_H
#define SHARD_H

#include "../shared/socket.h"
#include "../shared/listen_socket.h"
#include "../shared/common.h"
#include "game_server.h"
#include "user.h"

class Shard;

struct PaketHandler
{
    uint16 status;
    void (Shard::*handler)(ClientConnection* recvPacket);
};

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
///Local shard
class Shard : public ListenSocket, public Singleton<Shard>
{
    friend class ShardThread;
public:
    Shard(const char* listen_address, uint32 port);
    virtual ~Shard();
    void onClientConnectionRead(ClientConnection *pkt);
    void onClientConnectionDisconnect(Socket *sock)
    {
        --_conn_count;
        auto it = _user_sessions.find(sock);
        if (it != _user_sessions.end())
        {
            it->second->onSessionClose();
            _user_sessions.erase(sock);
        }
    };
    void onClientConnectionConnect(Socket *sock)
    {
        ++_conn_count;
    };
private:
    void performPacket( ClientConnection *pkt );
    FQueue<ClientConnection*> _data;

    PaketHandler _shardPacketHandlers[IG_MAX_ID];

    associative_container< Socket *, shared_ptr<User> > _user_sessions;
    AtomicCounter _conn_count;
};

#define iShard Shard::getSingletonPtr()

#endif // SHARD_H
