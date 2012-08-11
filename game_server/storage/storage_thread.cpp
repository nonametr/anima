#include "storage_thread.h"
#include "common.h"

StorageThread::StorageThread()
{
    shared_ptr<QueryResult> qres_save_period = shared_ptr<QueryResult> ( iDBManager->getSSDatabase()->queryNA ( "SELECT value FROM global WHERE param =\
\"save_period\"" ) );
    shared_ptr<QueryResult> qres_unload_period = shared_ptr<QueryResult> ( iDBManager->getSSDatabase()->queryNA ( "SELECT value FROM global WHERE param =\
\"unload_period\"" ) );
    if ( qres_save_period.get() == NULL && qres_unload_period.get() == NULL )
    {
        traceerr ( "Error loading global data from db!" );
        exit ( 1 );
    }
    Field *field = qres_save_period->fetch();
    _save_period = strToInt ( field[0].getString() );
    field = qres_unload_period->fetch();
    _unload_period = strToInt ( field[0].getString() );
}

StorageThread::~StorageThread()
{

}

void StorageThread::run()
{
    vector<uint> del_usrs;
    for ( uint32 i = 0; i < USER_HASH_SIZE; ++i )
    {
        iStorage->_users_hash_lock[i].lock();
        for ( auto it = iStorage->_users[i].begin(); it != iStorage->_users[i].end(); ++it )
        {
            if ( ( iStorage->getCurrentTime() - it->second->get ( "last_activity" )->getInt() ) < _save_period )
            {
                it->second->updateSql();
            }
            if ( ( iStorage->getCurrentTime() - it->second->get ( "last_activity" )->getInt() ) > _unload_period )
            {
                del_usrs.push_back ( it->first );
		traceerr("last_activity = %u, uid = %u", it->second->get ( "last_activity" )->getInt(), it->second->get("uid")->getInt());
            }
        }
        iStorage->_users_hash_lock[i].unlock();
    }
    sleep ( 10 );
    for ( uint i = 0; i < del_usrs.size(); ++i )
    {
      traceerr("OMG !!!!!!delete user!!!!!!!!");
//         iStorage->removeUser ( del_usrs[i] );
    }
}

