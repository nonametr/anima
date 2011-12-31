#ifndef PVP_INST_H
#define PVP_INST_H

#include "instance.h"

class PvpInstance : public Instance
{
public:
    void cJoin(ClientConnection* recvPacket);
private:
};

#endif // PVP_INST_H
