#include "debug_update.h"

DebugUpdate::DebugUpdate(LoginSocket *ls) : _running(true), _ls(ls)
{
}

DebugUpdate::~DebugUpdate()
{

}

void DebugUpdate::run()
{
    while (_running)
    {
        sleep(10);
// 	_ls->updateDb();
    }
    _running = !_running;
}

void DebugUpdate::onShutdown()
{
    _running = false;
    while (!_running)
    {
        sleep(1);
    }
}
