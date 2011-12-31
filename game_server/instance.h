#ifndef INST_H
#define INST_H

#include "../shared/net/socket.h"
#include "../shared/net/listen_socket.h"
#include "../shared/common.h"
#include "../game_server/user.h"

class Instance
{
public:
    virtual void cJoin(ClientConnection* pkt) = 0;
private:
    associative_container< Socket *, shared_ptr<User> > _user_sessions;
};

#endif // INST_H
