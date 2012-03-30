#include "command_structs.h"
#include "socket.h"
#include "packet_definitions.h"
#include "common.h"

Packet CInt64::create(uint32 v_uid, uint64 v_iVal1, int packet_type)
{
    CInt64 cVal;
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
	Packet send_pkt = OG_STR::create(0, MSG_PACKET_WRONG_DATA_SIZE);
        pkt->sock->send(&send_pkt);
        return shared_ptr<CInt64>();
    }
    memcpy(&ret_val, pkt->data, pkt->data_size);
    return ret_val;
}
Packet CInt32::create(uint32 v_uid, int v_iVal1, int packet_type)
{
    CInt32 cVal;
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
	Packet send_pkt = OG_STR::create(0, MSG_PACKET_WRONG_DATA_SIZE);
        pkt->sock->send(&send_pkt);
        return shared_ptr<CInt32>();
    }
    memcpy(&ret_val, pkt->data, pkt->data_size);
    return ret_val;
}
Packet OG_STR::create(uint32 v_uid, const char* v_strVal1)
{
    int len = strlen(v_strVal1);

    Packet pkt;
    pkt.data_size = len;
    pkt.type = Packets::OG_STR;
    pkt.crc32 = 0;
    pkt.data = new char[len];
    memset(pkt.data, 0, len);
    memcpy(pkt.data, v_strVal1, len);
    pkt.total_size = pkt.data_size + PACKET_HEADER_SIZE;

    return pkt;
}
shared_ptr<OG_STR> OG_STR::decompress(Packet *pkt)
{
    shared_ptr<OG_STR> ret_val(new OG_STR);
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





shared_ptr<IG_JOIN> IG_JOIN::decompress(Packet* pkt)
{
    char social_id[64] = {"\0"};
    shared_ptr<IG_JOIN> val(new IG_JOIN);
    int soc_id_len = pkt->data_size - sizeof(val->time);
    memcpy(social_id, pkt->data, soc_id_len);
    val->soc_id = atoll(social_id);
    memcpy(&val->time, &pkt->data[soc_id_len], sizeof(val->time));
    return val;
}
Packet OG_USER_DATA::create(string &json)
{
    int len = json.length();

    Packet pkt;
    pkt.data_size = len;
    pkt.type = Packets::OG_USER_DATA;
    pkt.crc32 = 0;
    pkt.data = new char[len];
    memset(pkt.data, 0, len);
    memcpy(pkt.data, json.c_str(), len);
    pkt.total_size = pkt.data_size + PACKET_HEADER_SIZE;

    return pkt;
}



