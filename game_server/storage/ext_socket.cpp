#include "ext_socket.h"

ExtSocket::ExtSocket ( const char* listen_address, uint32 port ) : ListenSocket(listen_address, port)
{
    ext_con_inst = new ExtSocketInstance(this);
}
ExtSocket::~ExtSocket() 
{ 
  delete ext_con_inst;
}
void ExtSocket::onPacketDisconnect ( Socket *sock )
{
    --_conn_count;
}
void ExtSocket::onPacketConnect ( Socket *sock )
{
    ++_conn_count;
}
void ExtSocket::onPacketRead(Packet *pkt)
{
    if ((Packets::EG_MIN_ID < pkt->type) && (pkt->type < Packets::EG_MAX_ID))
    {
        _data.push(pkt);
    }
    else
    {
	Packet send_pkt = OG_ERROR::create(0, intToString(MSG_PACKET_WRONG_ID).c_str());
	pkt->sock->send(&send_pkt);
	delete pkt;
    }
}
void ExtSocket::_performPacket ( Packet *pkt )
{
    ext_con_inst->handlePacket(pkt);
}
void ExtSocketThread::run()
{
    Packet* pkt = NULL;
    while (_running)
    {
        if (pkt != NULL)
        {
            owner->_performPacket( pkt );
            delete pkt;
        }

        pkt = owner->_data.pop( );
        if (pkt == NULL)
            sleep(1);
    }
}
void ExtSocketThread::onShutdown()
{
    _running = false;
    while(!_running){ sleep(1); }
}
ExtSocketThread::ExtSocketThread(ExtSocket *owner) : owner(owner), _running(true)
{
}
ExtSocketThread::~ExtSocketThread()
{
}
