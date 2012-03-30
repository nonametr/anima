#include "game_socket.h"

initialiseSingleton ( Packet );

void GameSocket::onPacketDisconnect(Socket *sock)
{
    --_conn_count;
}
void GameSocket::onPacketConnect(Socket *sock)
{
    ++_conn_count;
}
void GameSocket::onPacketRead(Packet *pkt)
{
    if ((Packets::IG_MIN_ID < pkt->type) && (pkt->type < Packets::IG_MAX_ID))
    {
        _data.push(pkt);
    }
    else
    {
        Packet send_pkt = OG_STR::create(0, MSG_PACKET_WRONG_ID);
        pkt->sock->send(&send_pkt);
        delete pkt;
    }
}
GameSocket::GameSocket(const char* listen_address, uint32 port) : ListenSocket(listen_address, port)
{
    _default_instance = new MainInstance(this);

    for (uint32 i = 0; i < iServer->getNumWorkerThreads(); ++i)
    {
        iThreadCore->startThread(new GameSocketThread(this));
    }
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
void GameSocket::_performPacket( Packet *pkt )
{
    Instance* inst;
    associative_container< Socket *, shared_ptr<Instance> >::iterator it_inst = _instances.find(pkt->sock);
    if (it_inst == _instances.end())
    {
        ///Set default instance
        changeInstance(pkt->sock, shared_ptr<Instance>(_default_instance));
        inst = _default_instance;
    }
    else
    {
        inst = it_inst->second.get();
    }
    inst->handlePacket(pkt);
}
GameSocket::~GameSocket()
{
    while (true)
    {
        Packet *pkt = _data.pop();
        if (pkt)
            delete pkt;
        else
            break;
        tracelog(OPTIMAL, "Clearing request queue... %u req. left", _data.get_size());
    }
    delete _default_instance;
}
void GameSocketThread::run()
{
    Packet* pkt = NULL;
    while (_running)
    {
        if (pkt != NULL)
        {
            shard_owner->_performPacket( pkt );
            delete pkt;
        }

        pkt = shard_owner->_data.pop( );
        if (pkt == NULL)
            sleep(1);
    }
    _running = !_running;
}
void GameSocketThread::onShutdown()
{
    _running = false;
    while (!_running) {
        sleep(1);
    }
}
GameSocketThread::GameSocketThread(GameSocket *owner) : shard_owner(owner), _running(true)
{
}
GameSocketThread::~GameSocketThread()
{
}

