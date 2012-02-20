#include "server.h"
#include <stdio.h>
#include "game_server.h"
#include "../login_server/login_server.h"

initialiseSingleton ( Server );

Server::Server()
{

}

Server::~Server()
{
    unlockDb(_pid);
}

Server* Server::create(string &work_dir, uint32 pid)
{
    Server *srv;
    uint32 server_type;
    Field *field;

    lockDb(work_dir, pid);
    if (!testDb(pid))
    {
        unlockDb(pid);
        return NULL;
    }
    shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->query(DB_SELECT_SERVER_SQL__PID, pid));
    if (!qres.get())
        return NULL;
    do
    {
        field = qres->fetch();
        server_type = field[12].getUInt32();

        if (server_type == GAME_SERVER)
        {
            srv = new GameServer;
        }
        else if (server_type == LOGIN_SERVER)
        {
	    srv = new LoginServer;
        }
        else
            return NULL;
        srv->_id = field[0].getUInt32();
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
	srv->_pid = pid;
	srv->_work_dir = work_dir;
    }
    while (qres->nextRow());
    return srv;
}
void Server::lockDb(string &work_dir, uint32 pid)
{
    iDBManager->getSSDatabase()->query(DB_LOCK_SQL__PID_WORK_PATH, pid, work_dir.c_str());
}
bool Server::testDb(uint32 pid)
{
    Field *field;
    uint32 count_locked;
    shared_ptr<QueryResult> qres(iDBManager->getSSDatabase()->query(DB_TEST_UNIQ_SQL__PID, pid));
    if (!qres.get())
        return false;
    do
    {
        field = qres->fetch();
        count_locked = field[0].getUInt32();
    }
    while (qres->nextRow());
    if (count_locked > 1)
    {
        traceerr("Error multiply server desc in DB config.");
        return false;
    }
    if (count_locked == 0)
    {
        traceerr("Error server allready running or not configured in DB config.");
        return false;
    }
    return true;
}
void Server::unlockDb(uint32 pid)
{
    iDBManager->getSSDatabase()->query(DB_UNLOCK_SQL__PID, pid);
}

