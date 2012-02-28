#include "command_structs.h"

#include "packet_definitions.h"

Packet C1Int::create(uint32 v_uid, int v_iVal1)
{
    C1Int cVal;
    cVal.uid = v_uid;
    cVal.iVal1 = v_iVal1;

    Packet pkt;
    pkt.data_size = sizeof(C1Int);
    pkt.type = EG_SET_MONEY;
    pkt.crc32 = 0;
    pkt.data = new char[sizeof(C1Int)];
    memcpy(&pkt.data[0], &cVal, sizeof(C1Int));
    pkt.total_size = pkt.data_size + PACKET_HEADER_SIZE;
    return pkt;
}
Packet C1Str::create(uint32 v_uid, string v_strVal1)
{
    C1Str cVal;
    cVal.uid = v_uid;
    cVal.strVal1 = v_strVal1;
    Packet pkt;

    return pkt;
}
Packet C2Int::create(uint32 v_uid, int v_iVal1, int v_iVal2)
{
    Packet pkt;
    return pkt;
}
Packet C2Int1Str::create(uint32 v_uid, int v_iVal1, int v_iVal2, string v_strVal1)
{
    Packet pkt;
    return pkt;
}
