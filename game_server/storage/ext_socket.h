#ifndef EXTERNAL_SHARD_H
#define EXTERNAL_SHARD_H

#include "socket.h"
#include "listen_socket.h"
#include "game_server.h"
#include "user_ext.h"
#include "ext_socket_instance.h"

#include <atomic>

class ExtSocketInstance;
class ExtSocket;

///This class used to communicate with other shards
class ExtSocket : public ListenSocket
{
    friend class ExtSocketThread;
public:
    ExtSocket ( const char* listen_address, uint32 port );
    virtual ~ExtSocket();

private:
    virtual void onPacketRead(Packet *pkt);
    virtual void onPacketDisconnect(Socket *sock);
    virtual void onPacketConnect(Socket *sock);
    
    void _performPacket ( Packet *pkt );
    FQueue<Packet*> _data;

    AtomicCounter _conn_count;

    ExtSocketInstance *ext_con_inst;
};
///ExtSocket MT
class ExtSocketThread : public Thread
{
public:
    virtual void run();
    virtual void onShutdown();
    ExtSocketThread(ExtSocket *owner);
    virtual ~ExtSocketThread();
private:
    ExtSocket *owner;
    volatile bool _running;
};

#endif // EXTERNAL_SHARD_H
