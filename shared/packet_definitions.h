#ifndef PACKET_DEFINITIONS_H
#define PACKET_DEFINITIONS_H

#define MSG_PACKET_NO_HEADER "Packet header not received or corrupted. Connection crushed and closed."
#define MSG_PACKET_WRONG_ID "Packet with that id can't be handled. Connection crushed and closed."
#define MSG_PACKET_FRAGMET "Packet expecting structure wrong or corrupted. Connection crushed and closed."

#define PACKET_INT_SIZE 4
#define PACKET_HEADER_SIZE PACKET_INT_SIZE*2

enum IG_PAKETS
{
    IG_JOIN = 1, IG_GET_PARAM, IG_LIST_PARAMS, IG_MAX_ID
};
enum OG_PAKETS
{
    OG_NAME = 10000, OG_GET_PARAM, OG_LIST_PARAMS, OG_MAX_ID
};

class Socket;

struct ClientConnection
{
    int type;
    int size;
    char *data;
    Socket *sock;
};

struct IGPacket
{
    int type;///packet type = IG paket id
    int size_total;///total packet size, including all from type to crc
    int crc32;///crc32 from all packet data
    char *data;///max data size = 128 bites
};
struct OGPacket
{
    int type;///packet type = OG paket id
    int size_total;///total packet size, including all from type to crc
    int crc32;///crc32 from all packet data
    char *data;///max data size = 128 bites
};

struct CrossPacket
{
    int type;///packet type = 1
    int size_total;///total packet size, including all from type to crc
    int crc32;///crc32 from all packet data
    char *data;///max data size = 128 bites
};

#endif
