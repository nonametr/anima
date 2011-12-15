#include "shard_ext.h"

void ShardExt::onClientConnectionDisconnect ( Socket *sock )
{
    for ( uint32 i = 0; i < _conn_count.getVal(); ++i )
    {
        _ext_connections[i]->mutex.lock();
        if ( _ext_connections[i]->sock == NULL )
        {
            _ext_connections[i]->mutex.unlock();
            continue;
        }
        if ( _ext_connections[i]->sock == sock )
        {
            _ext_connections[i]->sock = NULL;
        }
        _ext_connections[i]->mutex.unlock();
    }
    --_conn_count;
    traceerr ( "Connection to anima manager server was closed!" );
}
void ShardExt::onClientConnectionConnect ( Socket *sock )
{
    ++_conn_count;
    ASSERT_RETURN(_conn_count.getVal() < MAX_EXT_CONNECTIONS);
    for ( uint32 i = 0; i < _conn_count.getVal(); ++i )
    {
        _ext_connections[i]->mutex.lock();
        if ( _ext_connections[i]->sock != NULL )
        {
            _ext_connections[i]->mutex.unlock();
            continue;
        }
        _ext_connections[i]->sock = sock;
        _ext_connections[i]->mutex.unlock();
    }
}
ExtConnection* ShardExt::getFreeConnection()
{
    uint32 i = 0;
    for ( ;; )
    {
        ExtConnection* con = _ext_connections[ ( ( i++ ) % _conn_count.getVal() ) ];
        if ( con->mutex.try_lock() )
            return con;
    }

    // shouldn't be reached
    return NULL;
}
