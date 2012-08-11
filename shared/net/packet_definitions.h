#ifndef PACKET_DEFINITIONS_H
#define PACKET_DEFINITIONS_H

#define MSG_PACKET_NO_HEADER 5000
#define MSG_PACKET_WRONG_ID 5001
#define MSG_PACKET_WRONG_DATA_SIZE 5002
#define MSG_PACKET_FRAGMET 5003
#define MSG_PACKET_WRONG_ID_IN_THIS_INSTANCE 5004

#define PACKET_HEADER_COUNT 5
#define PACKET_INT_SIZE 4
#define PACKET_HEADER_SIZE PACKET_INT_SIZE*PACKET_HEADER_COUNT

#include "common.h"
#include "packet_id.h"
#include "command_structs.h"

class Socket;

struct Packet
{
    Packet()
    {}
    ~Packet()
    {}
///---BEGIN HEADER------------
    int type;
    uint total_size;
    uint data_size;
    int crc32;
    int packet_id;
///---END HEADER--------------

///---BEGIN BODY--------------
    string data;
///---END BODY----------------

///---BEGIN NON PACKET DATA---
    Socket *sock;
///---END NON PACKET DATA-----
};

#endif


