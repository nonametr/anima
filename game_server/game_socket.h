#ifndef SHARD_H
#define SHARD_H

#include "../shared/net/socket.h"
#include "../shared/net/listen_socket.h"
#include "../shared/common.h"
#include "game_server.h"
#include "user.h"
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

    virtual void onClientConnectionRead(char *pkt_data, int bytes_recv, Socket *sock)
    {
        ClientConnection *pkt = paketize(pkt_data, bytes_recv, sock);
        _data.push(pkt);
    }
    virtual void onClientConnectionDisconnect(Socket *sock) {
        --_conn_count;
    };
    virtual void onClientConnectionConnect(Socket *sock) {
        ++_conn_count;
    };

    void performPacket( ClientConnection *pkt );
    FQueue<ClientConnection*> _data;

    MainInstance *default_instance;
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
    AtomicBoolean _running;
};

#endif // SHARD_H
