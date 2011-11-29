#include <iostream>

#include "../shared/common.h"
#include "../shared/config.h"
#include "../shared/netcore.h"
#include "../shared/threadcore.h"
#include "../shared/periodicthreadcaller.h"
#include "../shared/json.h"
#include "../shared/jsonvalue.h"

// Just some sample JSON text, feel free to change but could break demo
const char* EXAMPLE = "\
{ \
\"user_name\" : \"NONAMETR\", \
\"bool_name\" : true, \
\"bool_second\" : FaLsE, \
\"null_name\" : nULl, \
\"negative\" : -34.276, \
\"sub_object\" : { \
\"foo\" : \"abc\", \
\"bar\" : 1.35e2, \
\"blah\" : { \"a\" : \"A\", \"b\" : \"B\", \"c\" : \"C\" } \
}, \
\"array_letters\" : [ \"a\", \"b\", \"c\", [ 1, 2, 3 ] ] \
} ";

bool ininializeSingletons()
{
    new Config;
    new NetCore;
    new ThreadCore;
    new PeriodicThreadCaller;///no need to delete at exit - it's auto runing thread and as all threads its managed by ThreadCore
}
bool destroy()
{
    delete iThreadCore;
    delete iConfig;
    delete iNetCore;
}
class TST : public Thread
{
public:
    void run() {
        traceerr("YOYO");
    };
    void onShutdown() {};
};
int main ( int argc, char **argv )
{
    ininializeSingletons();
    tracelog(4, "dasd %u", 213);
    TST *aaa = new TST();
    TST *vvv = new TST();
    iThreadCore->startThread(vvv);
    iPeriodicThreadCaller->startPeriodicThread(aaa, 1);
    JSONValue *value = JSON::Parse(EXAMPLE);
    JSONObject root;
    root = value->asObject();
    
    std::cout << "Hello, world! TEST GIT -------->" << root["user_name"]->asString().c_str() << std::endl;
    delete value;
     sleep(1);
    destroy();
    return 1;
}
