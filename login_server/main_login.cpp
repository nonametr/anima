#include <iostream>
#include <signal.h>
#include <sys/resource.h>

#include "loginserver.h"

int main ( int argc, char **argv )
{
    new Config;
    
    const char *cfg_file = NULL;
    int c = 1;
    while (c < argc)
    {
        if (strcmp(argv[c], "-c") == 0)
        {
            if (++c >= argc)
            {
                traceerr("Error: -c option requires an input argument");
                return -1;
            }
            else
                cfg_file = argv[c];
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

    tracelog(OPTIMAL, "Starting login server");
    new LoginServer;
    iLoginServer->run();

    delete iLoginServer;
    delete iConfig;

    return EXIT_SUCCESS;
}
