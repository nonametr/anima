#ifndef PACKET_DEFINITIONS_H
#define PACKET_DEFINITIONS_H

#define MSG_PACKET_NO_HEADER "Packet header not received or corrupted. Connection crushed and closed."
#define MSG_PACKET_WRONG_ID "Packet with that id can't be handled. Connection crushed and closed."
#define MSG_PACKET_FRAGMET "Packet expecting structure wrong or corrupted. Connection crushed and closed."

#define PACKET_INT_SIZE 4
#define PACKET_HEADER_SIZE PACKET_INT_SIZE*2

enum PACKETS {PACKET_NULL, PACKET_ECHO, PACKETS_MAX_ID};

class Socket;

struct Client
{
    int type;
    int size;
    char *data;
    Socket *connection;
};

struct PacketEcho
{
  int type;///packet type = 1
  int size_total;///total packet size, including all from type to crc  
  char data[128];///max data size = 128 bites
  int size;///usefull packet data size
  int crc32;///crc32 from usefull packet data
};

#endif