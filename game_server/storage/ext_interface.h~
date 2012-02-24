#ifndef EXTERNAL_SHARD_H
#define EXTERNAL_SHARD_H

#include "../../shared/net/socket.h"
#include "../../shared/net/listen_socket.h"
#include "../game_server.h"
#include "../user/user_ext.h"
#include <atomic>

#define EXT_CONNECTIONS 3

#define DB_GET_OTHER_SERVERS_SQL__PID "SELECT server_id, listen_ip, ext_port, server_type FROM server_desc WHERE online != %u AND online != 0"

struct ExtConnection
{
    Socket sock;
    Mutex mutex;
};

class ExtServer
{
public:
    ExtServer(uint32 server_id,
              string listen_ip,
              uint32 ext_port,
              uint32 server_port) : _server_id(server_id), _listen_ip(listen_ip), _ext_port(ext_port), _server_port(server_port)
    {};

    void send(const char *send_buf, uint32 size);
private:
    ExtConnection *_getFreeConnection();
    ExtConnection _ext_connections[EXT_CONNECTIONS];

    uint32 _server_id;
    string _listen_ip;
    uint32 _ext_port;
    uint32 _server_port;
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
class ExtSocket : public ListenSocket
{
    friend class ShardExtThread;
public:
    ExtSocket ( const char* listen_address, uint32 port );
    virtual ~ExtSocket() {};

private:
    virtual void onClientPacketRead(Packet *pkt);
    virtual void onClientPacketDisconnect(Socket *sock);
    virtual void onClientPacketConnect(Socket *sock);
    
    void _performExtPacket ( ExtPacket *pkt );
    FQueue<ClientPacket*> _data;

    AtomicCounter _conn_count;

    associative_container< uint32, ExtServer *> _ext_servers;//<server_id, connection>
};

#define iShardExt ShardExt::getSingletonPtr()

#endif // EXTERNAL_SHARD_H
