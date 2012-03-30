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
struct CInt32
{
    static Packet create(uint32 v_uid, int v_iVal1, int packet_type);
    static shared_ptr<CInt32> decompress(Packet *pkt);
    int iVal1;
};
struct OG_STR
{
    static Packet create(uint32 v_uid, const char* v_strVal1);
    static shared_ptr<OG_STR> decompress(Packet *pkt);
    char *strVal1;
    int size;
};
struct CInt32Int32
{
    static Packet create(uint32 v_uid, int v_iVal1, int v_iVal2, int packet_type);
    static shared_ptr<CInt32Int32> decompress(Packet *pkt);
    int iVal1;
    int iVal2;
};
struct IG_JOIN
{
    static shared_ptr<IG_JOIN> decompress(Packet *pkt);
    public:
      long long int soc_id;
      int time;
};
struct OG_USER_DATA
{
    static Packet create(string &json);
};
#endif
