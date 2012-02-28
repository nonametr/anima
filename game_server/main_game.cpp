#include <iostream>
#include <signal.h>
#include <sys/resource.h>
#include <unistd.h>
#include "server.h"
#include "common.h"

#include "game_server.h"
// #include "dict_json_generator.h"

Server* iServer;///extern global
uint32 dbg_lvl;///extern global
string err_log_path;///extern global
string srv_log_path;///extern global

#include <cstdlib>
#include <iostream>

void destroyObjects()
{
    if (iServer)
        delete iServer;
    if (iThreadCore)
        delete iThreadCore;
    if (iDBManager)
        delete iDBManager;
    if (iConfig)
        delete iConfig;
}
void initGlobals()
{
    dbg_lvl = OPTIMAL;
    srv_log_path = "start_srv.log";
    err_log_path = "start_err.log";
}
char* getArgConfigPath(int argc, char **argv)
{
    char *cfg_path = NULL;
    int c = 1;
    while (c < argc)
    {
        if (strcmp(argv[c], "-c") == 0)
        {
            if (++c >= argc)
            {
                break;
            }
            else
            {
                cfg_path = argv[c];
                break;
            }
        }
        ++c;
    }
    return cfg_path;
}
int main ( int argc, char **argv )
{
    initGlobals();

    uint32 pid;
    string work_dir(get_current_dir_name());
    new Config;
    bool restart = false;
    bool running = true;
    const char *cfg_file = getArgConfigPath(argc, argv);
    if (!cfg_file)
    {
        traceerr("Error! No config file specified!");
        destroyObjects();
        return EXIT_FAILURE;
    }

    iConfig->loadFromFile(cfg_file);///it will use default path to configuration file if cfg_file == NULL(default imposible) or no -c option passed

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
    
//     DictJSONGenerator *djg = new DictJSONGenerator;
//     delete djg;

    tracelog(OPTIMAL, "Starting server");
    while (running)
    {
        iServer = Server::create(work_dir, pid);
        if (!iServer)
        {
            traceerr("Error server can't start. Try check DB config or сontact your network administrator.");
            destroyObjects();
            break;
        }
        iServer->run();///infinity loop
        running = restart = iServer->isRestating();
	destroyObjects();
        if (restart)
        {
            new Config;
            tracelog(OPTIMAL, "Restarting server");
            iConfig->loadFromFile(cfg_file);
            new ThreadCore;
            new DatabaseManager;
            running = true;
        }
    }

    return EXIT_SUCCESS;
}


