#ifndef EXTERNAL_SHARD_H
#define EXTERNAL_SHARD_H

#include "../shared/socket.h"
#include "../shared/listen_socket.h"
#include "game_server.h"
#include "user_ext.h"
#include <atomic>

#define MAX_EXT_CONNECTIONS 16

struct ExtConnection
{
    Socket* sock;
    Mutex mutex;
};

class ShardExtThread : public Thread
{
public:
    void run();
    void onShutdown();
    ShardExtThread();
    virtual ~ShardExtThread();
private:
    AtomicBoolean _running;
};

///This class used to communicate with other shards
class ShardExt : public ListenSocket, public Singleton<ShardExt>
{
    friend class ShardExtThread;
public:
    ShardExt ( const char* listen_address, uint32 port );
    virtual ~ShardExt();
    void onClientConnectionRead ( ClientConnection *pkt )
    {
        _data.push ( pkt );
    };
    void onClientConnectionDisconnect ( Socket *sock );
    void onClientConnectionConnect ( Socket *sock );
    ExtConnection* getFreeConnection();
    template<class T>
    void getUserCallBack ( uint32 uid, void ( T::*handler ) ( shared_ptr<UserInterface> user ) )
    {
        //borring user data fetch code
        handler ( shared_ptr<UserExt>() );
    };
private:
    void _performPacket ( ClientConnection *pkt );
    FQueue<ClientConnection*> _data;
    ExtConnection* _ext_connections[MAX_EXT_CONNECTIONS];
    AtomicCounter _conn_count;
};

#define iShardExt ShardExt::getSingletonPtr()

#endif // EXTERNAL_SHARD_H
