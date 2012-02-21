#ifndef INST_H
#define INST_H

#include "../../shared/net/socket.h"
#include "../../shared/net/listen_socket.h"
#include "../../shared/common.h"
#include "../../game_server/user.h"

template <class T>
class PaketHandler
{
public:
    enum STATUS { NO_HANDLER_SET, HANDLER_SET} status;
    inline void setHandler(STATUS v_status, void (T::*p_handler)(ClientConnection* recvPacket)) 
    {
        status = v_status;
        handler = p_handler;
    };
    void (T::*handler)(ClientConnection* recvPacket);
};

class Instance
{
public:
    virtual void handlePaket(ClientConnection* pkt) = 0;
private:
    associative_container< Socket *, shared_ptr<User> > _user_sessions;
};

#endif // INST_H
