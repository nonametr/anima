#include "ext_server_manager.h"

initialiseSingleton ( ExtServerManager );

ExtServerManager::ExtServerManager()
{
    uint32 server_id;
    string listen_ip;
    uint32 ext_port;
    uint32 server_type;
    Field *field;
    shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->query(DB_GET_OTHER_SERVERS_SQL__PID, iServer->getPID()));
    if (!qres.get())
        return;
    do
    {
        field = qres->fetch();
        server_id = field[0].getUInt32();
        listen_ip = field[1].getString();
        ext_port = field[2].getUInt32();
        server_type = field[3].getUInt32();
        _ext_servers[server_id] = new ExtServerConnection(server_id, listen_ip, ext_port, server_type);
    }
    while (qres->nextRow());
}
ExtServerManager::~ExtServerManager()
{
}
ExtServerConnection *ExtServerManager::getByUid(int uid)
{
    Field *field;
    uint32 server_id;
    shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->query(DB_GET_ONLINE_USER__UID, uid));
    if (!qres.get())
        return NULL;

    field = qres->fetch();
    server_id = field[0].getUInt32();
    if (!server_id)
        return NULL;

    return _ext_servers[server_id];
}
ExtServerConnection *ExtServerManager::getById(int server_id)
{
    return _ext_servers[server_id];
}
ExtConnection *ExtServerConnection::_getFreeConnection()
{
    uint32 i = 0;
    for ( ;; )
    {
        ExtConnection *con = &_ext_connections[ ( ( i++ ) % EXT_CONNECTIONS ) ];
        if ( con->mutex.try_lock() )
            return con;
    }

    // shouldn't be reached
    return NULL;
}
void ExtServerConnection::sendPacket(Packet *pkt)
{
    char *send_buf = new char[pkt->total_size];
    memcpy(send_buf, pkt, pkt->total_size);
    ExtConnection *connection = _getFreeConnection();
    connection->mutex.lock();
    if (connection->sock.isConnected())
        connection->sock.send(send_buf, pkt->total_size);
    else
    {
        connection->sock.connect(_listen_ip.c_str(), _ext_port);
        connection->mutex.unlock();
        sendPacket(pkt);
    }
    connection->mutex.unlock();
}
