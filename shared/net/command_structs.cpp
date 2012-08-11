#include "command_structs.h"
#include "socket.h"
#include "packet_definitions.h"
#include "common.h"
#include "exeption.h"

Packet CInt64::create ( uint32 v_uid, uint64 v_iVal1, int packet_type )
{
    CInt64 cVal;
    cVal.iVal1 = v_iVal1;

    Packet pkt;
    pkt.type = packet_type;
    pkt.crc32 = 0;
    char buf[8] = {"\0"};
    memcpy ( &buf[0], &cVal, sizeof ( CInt64 ) );
    pkt.data = buf;
    pkt.data_size = pkt.data.size();
    pkt.total_size = pkt.data.size() + PACKET_HEADER_SIZE;
    return pkt;
}
shared_ptr<CInt64> CInt64::decompress ( Packet *pkt )
{
    shared_ptr<CInt64> ret_val ( new CInt64 );
    if ( sizeof ( ret_val ) != pkt->data.size() )
    {
        Packet send_pkt = OG_ERROR::create ( 0, intToString ( MSG_PACKET_WRONG_DATA_SIZE ).c_str() );
        pkt->sock->send ( &send_pkt );
        return shared_ptr<CInt64>();
    }
    memcpy ( &ret_val, pkt->data.c_str(), pkt->data.size() );
    return ret_val;
}
IG_2Int32 IG_2Int32::decompress ( Packet *pkt )
{
    IG_2Int32 ret_val;
    if ( sizeof ( IG_2Int32 ) != pkt->data.size() )
        ErrorExeption ( ErrorExeption::WRONG_PACKET_DATA, intToString ( __LINE__ ) +string ( " " ) + string ( __FUNCTION__ ) );
    memcpy ( &ret_val, pkt->data.c_str(), pkt->data.size() );
    return ret_val;
}
IG_Int32 IG_Int32::decompress ( Packet *pkt )
{
    IG_Int32 ret_val;
    if ( sizeof ( IG_Int32 ) != pkt->data.size() )
        ErrorExeption ( ErrorExeption::WRONG_PACKET_DATA, intToString ( __LINE__ ) +string ( " " ) + string ( __FUNCTION__ ) );
    memcpy ( &ret_val, pkt->data.c_str(), pkt->data.size() );
    return ret_val;
}
IG_STR IG_STR::decompress ( Packet* pkt )
{
    char *str = new char[pkt->data.size()];
    memset ( str, 0, pkt->data.size() );
    IG_STR val;

    memcpy ( str, pkt->data.c_str(), pkt->data.size() );
    val.str = string ( str );
    return val;
}
IG_JOIN IG_JOIN::decompress ( Packet* pkt )
{
    if ( pkt->data.size() >= 64 )
        ErrorExeption ( ErrorExeption::WRONG_PACKET_DATA, intToString ( __LINE__ ) +string ( " " ) + string ( __FUNCTION__ ) );
    char social_id[64] = {"\0"};
    IG_JOIN val;
    memcpy ( social_id, pkt->data.c_str(), pkt->data.size() );
    val.soc_id = atoll ( social_id );
    return val;
}
///------------OUTGOING_PACKET_DATA_TYPES------------------
Packet OG_ERROR::create ( uint32 v_uid, const char* v_strVal1 )
{
    Packet pkt;
    pkt.type = Packets::OG_ERROR;
    pkt.crc32 = 0;
    pkt.data = string ( "{\"msg\":\"" ) + string ( v_strVal1 ) + string ( "\"}" );
    pkt.data_size = pkt.data.size();
    pkt.total_size = pkt.data.size() + PACKET_HEADER_SIZE;

    return pkt;
}
Packet OG_USER_JSON::create ( string &json )
{
    Packet pkt;
    pkt.type = Packets::OG_USER_JSON;
    pkt.crc32 = 0;
    pkt.data = json;
    pkt.data_size = pkt.data.size();
    pkt.total_size = pkt.data.size() + PACKET_HEADER_SIZE;

    return pkt;
}



