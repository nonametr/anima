#ifndef INST_H
#define INST_H

#include "socket.h"
#include "listen_socket.h"
#include "common.h"
#include "user.h"

template <class T>
class PacketHandler
{
public:
    enum STATUS { NO_HANDLER_SET, HANDLER_SET} status;
    inline void setHandler(STATUS v_status, void (T::*p_handler)(User* usr, Packet* recvPacket)) 
    {
        status = v_status;
        handler = p_handler;
    };
    void (T::*handler)(User* usr, Packet* recvPacket);
};

class Instance
{
public:
    virtual void handlePacket(Packet* pkt) = 0;
private:
    associative_container< Socket *, User* > _user_sessions;
};

#endif // INST_H
