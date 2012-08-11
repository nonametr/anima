#ifndef EXT_SERVER_MANAGER_H
#define EXT_SERVER_MANAGER_H

#include "singleton.h"
#include "game_server.h"
#include "sql_define.h"

#define EXT_CONNECTIONS 3

struct ExtConnection
{
    Socket sock;
    Mutex mutex;
};

class ExtServerConnection
{
public:
    ExtServerConnection(uint32 server_id,
              string listen_ip,
              uint32 ext_port,
              uint32 server_port) : _server_id(server_id), _listen_ip(listen_ip), _ext_port(ext_port), _server_port(server_port)
    {};

    void sendPacket(Packet *pkt);
private:
    ExtConnection *_getFreeConnection();
    ExtConnection _ext_connections[EXT_CONNECTIONS];

    uint32 _server_id;
    string _listen_ip;
    uint32 _ext_port;
    uint32 _server_port;
};

class ExtServerManager : public Singleton<ExtServerManager>
{
public:
    ExtServerManager();
    ~ExtServerManager();
    
    ExtServerConnection *getByUid(int uid);
    ExtServerConnection *getById(int server_id);
private:
    associative_container< uint32, ExtServerConnection *> _ext_servers;//<server_id, connection>
};

#define iExtServerManager ExtServerManager::getSingletonPtr()

#endif // EXT_SERVER_MANAGER_H
