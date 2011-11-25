#include <iostream>
#include "./shared/config.h"
#include "./shared/netcore.h"
#include "./shared/threadcore.h"

bool ininializeSingletons()
{
    new Config;
    new NetCore;
    new ThreadCore;
}
int main ( int argc, char **argv )
{
    ininializeSingletons();
    std::cout << "Hello, world! TEST GIT" << std::endl;
    return 0;
}
