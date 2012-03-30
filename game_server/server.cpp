#include "server.h"
#include <stdio.h>
#include "game_server.h"

initialiseSingleton ( Server );

Server::Server()
{
}

Server::~Server()
{
}
void Server::restart()
{
    _need_restart.setVal ( true );
    stop();
}
bool Server::isRestating()
{
    return _need_restart.getVal();
}
void Server::stop()
{
    _running = false;
}
Server* Server::create ( string &work_dir, uint32 pid )
{
    Server *srv;
    Field *field;

    shared_ptr<QueryResult> qres ( iDBManager->getSSDatabase()->query ( DB_SELECT_SERVER_SQL__PID, pid ) );
    if ( !qres.get() || qres.get()->getRowCount() > 1 )
        return NULL;

    field = qres->fetch();

    srv = new GameServer;
    srv->_id = field[0].getUInt32();
    iDBManager->getSSDatabase()->execute ( DB_RESET_ALL_USERS_IN_MEMORY__SERVER_ID, srv->_id );
    srv->_listen_ip = field[1].getString();
    srv->_port = field[2].getUInt32();
    srv->_ext_port = field[3].getUInt32();
    srv->_daemon_user = field[4].getString();
    srv->_daemon_dir = field[5].getString();
    err_log_path = field[6].getString();
    srv_log_path = field[7].getString();
    dbg_lvl = field[8].getUInt32();
    srv->_num_net_threads = field[9].getUInt32();
    srv->_num_worker_threads = field[10].getUInt32();
    srv->_version_control_system_name = field[11].getString();
    srv->_http_port = field[12].getUInt32();
    srv->_pid = pid;
    srv->_work_dir = work_dir;

    return srv;
}
