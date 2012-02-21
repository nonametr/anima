#ifndef EXTERNAL_SHARD_H
#define EXTERNAL_SHARD_H

#include "../shared/net/socket.h"
#include "../shared/net/listen_socket.h"
#include "game_server.h"
#include "user_ext.h"
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
class ExtInterface : public ListenSocket, public Singleton<ExtInterface>
{
    friend class ShardExtThread;
public:
    ExtInterface ( const char* listen_address, uint32 port );
    virtual ~ExtInterface() {};

//     template<class T>
//     void getUserCallBack ( uint32 uid, void ( T::*handler ) ( shared_ptr<UserInterface> user ) )
//     {
//         //borring user data fetch code
//         handler ( shared_ptr<UserExt>() );
//     };
private:
    void onClientConnectionDisconnect ( Socket *sock );
    void onClientConnectionConnect ( Socket *sock );
    void onClientConnectionRead ( ClientConnection *pkt ){ _data.push ( pkt ); };
    
    void _performPacket ( ClientConnection *pkt );
    FQueue<ClientConnection*> _data;

    AtomicCounter _conn_count;

    associative_container< uint32, ExtServer *> _ext_servers;//<server_id, connection>
};

#define iShardExt ShardExt::getSingletonPtr()

#endif // EXTERNAL_SHARD_H
