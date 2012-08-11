#include "user_ext.h"
#include "command_structs.h"
#include "ext_server_manager.h"

UserExt::UserExt(uint32 uid, uint32 server_id) : _uid(uid), _server_id(server_id)
{

}
UserExt::~UserExt()
{

}
///--------------SETTERS----------------
// void UserExt::setMoney(int v_money)
// {
//     Packet pkt = CInt32::create(_uid, v_money, EG_SET_MONEY);
// 
//     ExtServerConnection *connection = iExtServerManager->getById(_server_id);
//     if (connection == NULL)
//     {
//         return;
//     }
// 
//     connection->sendPacket(&pkt);
// }

///-------------GETTERS-----------------


