#ifndef SHARD_H
#define SHARD_H

#include "../shared/net/socket.h"
#include "../shared/net/listen_socket.h"
#include "../shared/common.h"
#include "game_server.h"
#include "user.h"
#include "instance.h"

class ShardSoket;

struct PaketHandler
{
    uint16 status;
    void (ShardSoket::*handler)(ClientConnection* recvPacket);
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

///Local shard soket
class ShardSoket : public ListenSocket, public Singleton<ShardSoket>
{
    friend class ShardThread;
public:
    ShardSoket(const char* listen_address, uint32 port);
    virtual ~ShardSoket();
private:

    void onClientConnectionRead(ClientConnection *pkt){ _data.push(pkt); }
    void onClientConnectionDisconnect(Socket *sock){ --_conn_count; };
    void onClientConnectionConnect(Socket *sock){ ++_conn_count; };
    
    void cJoin(ClientConnection* recvPacket);

    void performPacket( ClientConnection *pkt );
    FQueue<ClientConnection*> _data;

    PaketHandler _shardPacketHandlers[IG_MAX_ID];
   
    associative_container< Socket *, shared_ptr<Instance> > _instances;
    associative_container< uint32, Socket *> _uids;
    
    AtomicCounter _conn_count;
};

#define iShard ShardSoket::getSingletonPtr()

#endif // SHARD_H
