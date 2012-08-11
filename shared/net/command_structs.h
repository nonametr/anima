#ifndef COMMANDS_H
#define COMMANDS_H

#include "common.h"
#include "packet_id.h"

class Packet;

struct CInt64
{
    static Packet create(uint32 v_uid, uint64 v_iVal1, int packet_type);
    static shared_ptr<CInt64> decompress(Packet *pkt);
    uint64 iVal1;
};
struct IG_2Int32
{
    static IG_2Int32 decompress(Packet *pkt);
    int iVal1;
    int iVal2;
};


struct IG_Int32
{
    IG_Int32():iVal1(0){}
    static IG_Int32 decompress(Packet *pkt);
    int iVal1;
};
struct IG_JOIN
{
    IG_JOIN():soc_id(0){}
    static IG_JOIN decompress(Packet *pkt);
    long long int soc_id;
};
struct IG_STR
{
    IG_STR(){}
    static IG_STR decompress(Packet *pkt);
    string str;
};
struct OG_USER_JSON
{
    static Packet create(string &json);
};
struct OG_ERROR
{
    static Packet create(uint32 v_uid, const char* v_strVal1);
};
#endif
