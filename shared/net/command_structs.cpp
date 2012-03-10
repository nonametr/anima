#include "command_structs.h"
#include "socket.h"
#include "packet_definitions.h"

Packet CInt64::create(uint32 v_uid, uint64 v_iVal1, int packet_type)
{
    CInt64 cVal;
    cVal.uid = v_uid;
    cVal.iVal1 = v_iVal1;

    Packet pkt;
    pkt.data_size = sizeof(CInt64);
    pkt.type = packet_type;
    pkt.crc32 = 0;
    pkt.data = new char[sizeof(CInt64)];
    memcpy(&pkt.data[0], &cVal, sizeof(CInt64));
    pkt.total_size = pkt.data_size + PACKET_HEADER_SIZE;
    return pkt;
}
shared_ptr<CInt64> CInt64::decompress(Packet *pkt)
{
    shared_ptr<CInt64> ret_val(new CInt64);
    if (sizeof(ret_val)!= pkt->data_size)
    {
        pkt->sock->send(MSG_PACKET_WRONG_DATA_SIZE, strlen(MSG_PACKET_WRONG_DATA_SIZE));
        return shared_ptr<CInt64>();
    }
    memcpy(&ret_val, pkt->data, pkt->data_size);
    return ret_val;
}
Packet CInt32::create(uint32 v_uid, int v_iVal1, int packet_type)
{
    CInt32 cVal;
    cVal.uid = v_uid;
    cVal.iVal1 = v_iVal1;

    Packet pkt;
    pkt.data_size = sizeof(CInt32);
    pkt.type = packet_type;
    pkt.crc32 = 0;
    pkt.data = new char[sizeof(CInt32)];
    memcpy(&pkt.data[0], &cVal, sizeof(CInt32));
    pkt.total_size = pkt.data_size + PACKET_HEADER_SIZE;
    return pkt;
}
shared_ptr<CInt32> CInt32::decompress(Packet *pkt)
{
  shared_ptr<CInt32> ret_val(new CInt32);
    if (sizeof(ret_val)!= pkt->data_size)
    {
        pkt->sock->send(MSG_PACKET_WRONG_DATA_SIZE, strlen(MSG_PACKET_WRONG_DATA_SIZE));
        return shared_ptr<CInt32>();
    }
    memcpy(&ret_val, pkt->data, pkt->data_size);
    return ret_val;
}
Packet CStr32::create(uint32 v_uid, char* v_strVal1, int packet_type)
{
//     CStr32 cVal;
//     cVal.uid = v_uid;
//     cVal.strVal1 = v_strVal1;
    Packet pkt;

    return pkt;
}
shared_ptr<CStr32> CStr32::decompress(Packet *pkt)
{
    shared_ptr<CStr32> ret_val(new CStr32);
    return ret_val;
}
Packet CInt32Int32::create(uint32 v_uid, int v_iVal1, int v_iVal2, int packet_type)
{
    Packet pkt;
    return pkt;
}
shared_ptr<CInt32Int32> CInt32Int32::decompress(Packet *pkt)
{
    shared_ptr<CInt32Int32> ret_val(new CInt32Int32);
    return ret_val;
}
Packet CInt32Int32Str32::create(uint32 v_uid, int v_iVal1, int v_iVal2, char* v_strVal1, int packet_type)
{
    Packet pkt;
    return pkt;
}
shared_ptr<CInt32Int32Str32> CInt32Int32Str32::decompress(Packet *pkt)
{
    shared_ptr<CInt32Int32Str32> ret_val(new CInt32Int32Str32);
    return ret_val;
}

