#include "game_socket.h"

initialiseSingleton ( ClientPacket );

void GameSocket::onClientPacketDisconnect(Socket *sock)
{
    --_conn_count;
}
void GameSocket::onClientPacketConnect(Socket *sock)
{
    ++_conn_count;
}
void GameSocket::onClientPacketRead(Packet *pkt)
{
    ClientPacket *client_pkt = _createClientPacket(pkt);
    delete pkt;
    if (client_pkt)
        _data.push(client_pkt);
}
GameSocket::GameSocket(const char* listen_address, uint32 port) : ListenSocket(listen_address, port)
{
    _default_instance = new MainInstance(this);

    for (uint32 i = 0; i < iServer->getNumWorkerThreads(); ++i)
    {
        iThreadCore->startThread(new GameSocketThread(this));
    }
}
ClientPacket* GameSocket::_createClientPacket(Packet *pkt)
{
    ClientPacket *client_pkt = new ClientPacket;
    Socket *sock = client_pkt->sock = pkt->sock;

    if (pkt->data_size < PACKET_HEADER_SIZE)
    {
        traceerr("Error rcv packet without header");
        sock->send(MSG_PACKET_NO_HEADER, strlen(MSG_PACKET_NO_HEADER));
        sock->disconnect();
        delete client_pkt;
        return NULL;
    }
    memcpy(&client_pkt->type, &pkt->data.c_str()[0], PACKET_INT_SIZE);
    memcpy(&client_pkt->data_size, &pkt->data.c_str()[PACKET_INT_SIZE], PACKET_INT_SIZE);
    if (client_pkt->type >= IG_MAX_ID)
    {
        traceerr("Error rcv packet with id graiter than possible. Can't handle it!");
        sock->send(MSG_PACKET_WRONG_ID, strlen(MSG_PACKET_NO_HEADER));
        sock->disconnect();
        delete client_pkt;
        return NULL;
    }
    if (client_pkt->data_size != pkt->data_size)
    {
        traceerr("Error rcv packet fragmented or corrupted. Can't handle it!");
        sock->send(MSG_PACKET_FRAGMET, strlen(MSG_PACKET_NO_HEADER));
        sock->disconnect();
        delete client_pkt;
        return NULL;
    }
    client_pkt->data_size -= 3*sizeof(int);///3 ints - service data;
    client_pkt->data = string(pkt->data.c_str()[3*sizeof(int)], pkt->data_size);
    return client_pkt;
}
void GameSocket::changeInstance(Socket *owner, shared_ptr<Instance> new_instance)
{
    associative_container< Socket *, shared_ptr<Instance> >::iterator it_inst = _instances.find(owner);
    if (it_inst != _instances.end())
    {
        _instances.erase(it_inst);
    }
    _instances[owner] = new_instance;
}
void GameSocket::_performClientPacket( ClientPacket *pkt )
{
    associative_container< Socket *, shared_ptr<Instance> >::iterator it_inst = _instances.find(pkt->sock);
    if (it_inst == _instances.end())
    {
        ///Set default instance
        changeInstance(pkt->sock, shared_ptr<Instance>(_default_instance));
    }
    it_inst->second->handlePaket(pkt);
}
GameSocket::~GameSocket()
{
    while (true)
    {
        ClientPacket *pkt = _data.pop();
        if (pkt)
            delete pkt;
        else
            break;
        tracelog(OPTIMAL, "Clearing request queue... %u req. left", _data.get_size());
    }
}
void GameSocketThread::run()
{
    ClientPacket* pkt = NULL;
    while (_running.getVal())
    {
        if (pkt != NULL)
        {
            shard_owner->_performClientPacket( pkt );
            delete pkt;
        }

        pkt = shard_owner->_data.pop( );
        if (pkt == NULL)
            sleep(1);
    }
}
void GameSocketThread::onShutdown()
{
    _running.setVal(false);
}
GameSocketThread::GameSocketThread(GameSocket *owner) : shard_owner(owner)
{
    _running.setVal(true);
}
GameSocketThread::~GameSocketThread()
{
}

