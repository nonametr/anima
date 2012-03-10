#ifndef COMMANDS_H
#define COMMANDS_H

#include "common.h"

class Packet;

struct CInt64
{
    static Packet create(uint32 v_uid, uint64 v_iVal1, int packet_type);
    static shared_ptr<CInt64> decompress(Packet *pkt);
    uint uid;
    uint64 iVal1;
};
struct CInt32
{
    static Packet create(uint32 v_uid, int v_iVal1, int packet_type);
    static shared_ptr<CInt32> decompress(Packet *pkt);
    uint32 uid;
    int iVal1;
};
struct CStr32
{
    static Packet create(uint32 v_uid, char* v_strVal1, int packet_type);
    static shared_ptr<CStr32> decompress(Packet *pkt);
    uint32 uid;
    char strVal1[32];
};
struct CInt32Int32
{
    static Packet create(uint32 v_uid, int v_iVal1, int v_iVal2, int packet_type);
    static shared_ptr<CInt32Int32> decompress(Packet *pkt);
    uint32 uid;
    int iVal1;
    int iVal2;
};
struct CInt32Int32Str32
{
    static Packet create(uint32 v_uid, int v_iVal1, int v_iVal2, char* v_strVal1, int packet_type);
    static shared_ptr<CInt32Int32Str32> decompress(Packet *pkt);
    uint32 uid;
    int iVal1;
    int iVal2;
    char strVal1[32];
};

#endif
