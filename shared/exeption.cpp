#include "exeption.h"
#include "packet_definitions.h"
#include "socket.h"
#include "dict_manager.h"

void ErrorExeption::emitError ( Packet *pkt, uint err_msg_id )
{
  try
  {
    string &msg = iDictManager->getMsg ( err_msg_id );
    traceerr ( "%s [%s]", msg.c_str(), _line.c_str() );
    Packet send_pkt = OG_ERROR::create ( 0, intToString ( err_msg_id ).c_str() );
    pkt->sock->send ( &send_pkt );

  }
  catch(...)
  {
    traceerr ( "%s [%s]", "Error exeption! **Message not found in dict**", _line.c_str() );
    Packet send_pkt = OG_ERROR::create ( 0, intToString ( err_msg_id ).c_str() );
    pkt->sock->send ( &send_pkt );
  }
}

void ErrorExeption::doCatch ( Packet *pkt )
{
    switch ( err_code )
    {
    default:
        emitError ( pkt, err_code );
        break;
    }
}
