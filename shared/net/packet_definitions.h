#ifndef PACKET_DEFINITIONS_H
#define PACKET_DEFINITIONS_H

#define MSG_PACKET_NO_HEADER "Packet header not received or corrupted. Connection crushed and closed."
#define MSG_PACKET_WRONG_ID "Packet with that id can't be handled. Connection crushed and closed."
#define MSG_PACKET_WRONG_DATA_SIZE "Expected another size of data of packet with that id thats why pkt can't be handled. Connection crushed and closed."
#define MSG_PACKET_FRAGMET "Packet expecting structure wrong or corrupted. Connection crushed and closed."
#define MSG_PACKET_WRONG_ID_IN_THIS_INSTANCE "Packet with that id can't be handled by current instance. Connection crushed and closed."

#define PACKET_HEADER_COUNT 5
#define PACKET_INT_SIZE 4
#define PACKET_HEADER_SIZE PACKET_INT_SIZE*PACKET_HEADER_COUNT

#include "common.h"
#include "packet_id.h"
#include "command_structs.h"

class Socket;

struct Packet
{
    Packet() : data(NULL)
    {
    }
    ~Packet()
    {
        if (data != NULL)
            delete [] data;
    }
///---BEGIN HEADER------------
    int type;
    int total_size;
    int data_size;
    int crc32;
    int packet_id;
///---END HEADER--------------

///---BEGIN BODY--------------
    char *data;
///---END BODY----------------

///---BEGIN NON PACKET DATA---
    Socket *sock;
///---END NON PACKET DATA-----
};

#endif


