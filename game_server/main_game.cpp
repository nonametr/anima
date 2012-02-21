#include <iostream>
#include <signal.h>
#include <sys/resource.h>
#include <unistd.h>
#include "../game_server/server.h"
#include "../shared/common.h"

#include "game_server.h"
#include "../dict_json_generator.h"

Server* iServer;///extern global
uint32 dbg_lvl;///extern global
string err_log_path;///extern global
string srv_log_path;///extern global

#include <cstdlib>
#include <iostream>

void initGlobals()
{
    dbg_lvl = OPTIMAL;
    srv_log_path = "start_srv.log";
    err_log_path = "start_err.log";
}
int main ( int argc, char **argv )
{
    initGlobals();
    
    uint32 pid;
    string work_dir(get_current_dir_name());
    new Config;
    bool restart;
    bool running = true;
    const char *cfg_file = NULL;
    int c = 1;
    while (c < argc)
    {
        if (strcmp(argv[c], "-c") == 0)
        {
            if (++c >= argc)
            {
                return -1;
            }
            else
            {
                cfg_file = argv[c];
                break;
            }
        }
        ++c;
    }

    iConfig->loadFromFile(cfg_file);///it will use default path to configuration file if no -c option passed

    rlimit rl;
    if (getrlimit(RLIMIT_CORE, &rl) == -1)
    {
        traceerr("Getrlimit failed. This could be problem.\n");
    }
    else
    {
        rl.rlim_cur = rl.rlim_max;
        if (setrlimit(RLIMIT_CORE, &rl) == -1)
            traceerr("Setrlimit failed. Server may not save core.dump files.\n");
    }
    /** write pid file */
    FILE* fPid = fopen("anima.pid", "w");
    if (fPid)
    {
        pid = getpid();
        fprintf(fPid, "%u", (uint32)pid);
        fclose(fPid);
    }
    
    new ThreadCore;
    new DatabaseManager;
    DictJSONGenerator *djg = new DictJSONGenerator;
    delete djg;
    
    tracelog(OPTIMAL, "Starting server");
    while (running)
    {
        iServer = Server::create(work_dir, pid);
	if(!iServer)
	{
	  traceerr("Error server can't start. Try check DB config or сontact your network administrator.");
	  delete iConfig;
	  break;
	}
        iServer->run();
        restart = iServer->isRestating();
        delete iServer;
        delete iConfig;
        if (restart)
        {
            new Config;
	    tracelog(OPTIMAL, "Restarting server");
            iConfig->loadFromFile(cfg_file);
            running = true;
        }
    }

    return EXIT_SUCCESS;
}


