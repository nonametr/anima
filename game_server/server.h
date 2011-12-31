#ifndef SERVER_H
#define SERVER_H

#include "../shared/common.h"
#include "../game_server/database_manager.h"

#define DB_LOCK_SQL__PID_WORK_PATH "UPDATE server_desc SET online = %u WHERE active = 1 AND online = 0 AND daemon_dir = \"%s\""
#define DB_UNLOCK_SQL__PID "UPDATE server_desc SET online = 0 WHERE active = 1 AND online = %u"
#define DB_TEST_UNIQ_SQL__PID "SELECT count(*) FROM server_desc WHERE online = %u"
#define DB_SELECT_SERVER_SQL__PID "SELECT server_id, listen_ip, port, ext_port, daemon_user, daemon_dir, error_log_path, srv_log_path, dbg_lvl, num_net_threads, num_worker_threads, version_control_system_name, server_type FROM server_desc WHERE online = %u"

#define GAME_SERVER 0
#define LOGIN_SERVER 1

class Server : public Singleton<Server>
{
public:
    static Server* create(string &work_dir, uint32 pid);
   
    Server();
    virtual ~Server();
    virtual bool isRestating() = 0;
    virtual void run() = 0;
    virtual void restart() = 0;
    virtual void stop() = 0;
    
    uint32 getPID() { return _pid; };
    uint32 getNumWorkerThreads() { return _num_worker_threads; };
    uint32 getNumNetThreads() { return _num_net_threads; };
    string getVersionControlSystemName() { return _version_control_system_name; };
protected:
    static void lockDb(string &work_dir, uint32 pid);
    static bool testDb(uint32 pid);
    static void unlockDb(uint32 pid);
    
    uint32 _id;
    string _listen_ip;
    uint32 _port;
    uint32 _ext_port;
    string _daemon_dir;
    uint32 _num_net_threads;
    uint32 _num_worker_threads;
    string _daemon_user;
    string _version_control_system_name;
    uint32 _pid;
    string _work_dir;
};
#endif // SERVER_H
