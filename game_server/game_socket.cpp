#include "game_socket.h"

initialiseSingleton ( GameSocket );

GameSocket::GameSocket(const char* listen_address, uint32 port) : ListenSocket(listen_address, port)
{
    default_instance = new MainInstance(this);

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
void GameSocket::performPacket( ClientConnection *pkt )
{
    associative_container< Socket *, shared_ptr<Instance> >::iterator it_inst = _instances.find(pkt->sock);
    if (it_inst == _instances.end())
    {
        ///Set default instance
        changeInstance(pkt->sock, shared_ptr<Instance>(default_instance));
    }
    it_inst->second->handlePaket(pkt);
}
GameSocket::~GameSocket()
{
    while (true)
    {
        ClientConnection *pkt = _data.pop();
        if (pkt)
            delete pkt;
        else
            break;
        tracelog(OPTIMAL, "Clearing request queue... %u req. left", _data.get_size());
    }
}
void GameSocketThread::run()
{
    ClientConnection* pkt = NULL;
    while (_running.getVal())
    {
        if (pkt != NULL)
        {
            shard_owner->performPacket( pkt );
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

