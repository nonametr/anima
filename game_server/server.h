#ifndef SERVER_H
#define SERVER_H

#include "common.h"
#include "database_manager.h"
#include "sql_define.h"

class Server : public Singleton<Server>
{
public:
    static Server* create(string &work_dir, uint32 pid);
   
    Server();
    virtual ~Server();
    virtual void run() = 0;
    
    void restart();
    bool isRestating();
    void stop();
    bool isRunning(){ return _running; };
    
    uint32 getId() { return _id; };
    uint32 getPID() { return _pid; };
    uint32 getNumWorkerThreads() { return _num_worker_threads; };
    uint32 getNumNetThreads() { return _num_net_threads; };
    string getVersionControlSystemName() { return _version_control_system_name; };
protected:
    
    uint32 _id;
    string _listen_ip;
    uint32 _port;
    uint32 _http_port;
    uint32 _ext_port;
    string _daemon_dir;
    uint32 _num_net_threads;
    uint32 _num_worker_threads;
    string _daemon_user;
    string _version_control_system_name;
    uint32 _pid;
    string _work_dir;
     
    volatile bool _running;
    AtomicBoolean _need_restart;
};
#endif // SERVER_H
