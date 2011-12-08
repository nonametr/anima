#ifndef PACKET_DEFS_H
#define PACKET_DEFS_H

#define PACKET_HEADER_SIZE 4
#define PACKET_ECHO_ID 1

struct PacketEcho
{
  int type;///packet type = 1
  char data[128];///max data size = 128 bites
  int size;///usefull packet data size
  int crc;///crc32 from usefull packet data;
}

#endif PACKET_DEFS_H