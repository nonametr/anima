#ifndef COMMANDS_H
#define COMMANDS_H

#include "common.h"

class Packet;

struct JoinData
{
    uint32 uid;
    char sid[64];
};

struct C1Int
{
    static Packet create(uint32 v_uid, int v_iVal1);
    uint32 uid;
    int iVal1;
};
struct C1Str
{
    static Packet create(uint32 v_uid, string v_strVal1);
    uint32 uid;
    string strVal1;
};
struct C2Int
{
    static Packet create(uint32 v_uid, int v_iVal1, int v_iVal2);
    uint32 uid;
    int iVal1;
    int iVal2;
};
struct C2Int1Str
{
    static Packet create(uint32 v_uid, int v_iVal1, int v_iVal2, string v_strVal1);
    uint32 uid;
    int iVal1;
    int iVal2;
    string strVal1;
};

#endif
