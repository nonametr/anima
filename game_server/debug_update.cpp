#include "debug_update.h"

DebugUpdate::DebugUpdate(LoginSocket *ls)
{
    _ls = ls;
}

DebugUpdate::~DebugUpdate()
{

}

void DebugUpdate::run()
{
    while (_running)
    {
        sleep(1);
	_ls->updateDb();
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
