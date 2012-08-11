#include "database_manager.h"

initialiseSingleton ( DatabaseManager );

DatabaseManager::DatabaseManager(string work_dir, uint32 pid) : _ss_db ( NULL ), _pid(pid)
{
    int db_id;
    Field *fields;
    _ss_db = new MySQLDatabase;
    bool res = _ss_db->initialize ( iConfig->getParam ( Config::SSD_IP ).c_str(), iConfig->getParam ( Config::SSD_PORT ),
                                    iConfig->getParam ( Config::SSD_USER ).c_str(), iConfig->getParam ( Config::SSD_PASSWORD ).c_str(),
                                    iConfig->getParam ( Config::SSD_NAME ).c_str(), 2, 16384 );
    if ( !res )
    {
        traceerr ( "SQL connection to ss_db error. Server terminated." );
        exit ( 0 );
    }



    _ss_db->queryNA ( "UPDATE server_desc SET online_pid = 0");//!!!!!!!!!!!TEST!!!!!!!!!!!!




    lockDb ( work_dir, pid );
    if ( !testDb ( pid ) )
    {
        unlockDb ( pid );
        exit(0);
    }

    shared_ptr<QueryResult> q_db_count ( _ss_db->queryNA ( DB_GET_COUNT ) );
    shared_ptr<QueryResult> q_db_desc ( _ss_db->queryNA ( DB_GET_DESC ) );

    if ( !q_db_count.get() || !q_db_desc.get() )
    {
        traceerr ( "Error fetching db desc data!" );
        return;
    }
    fields = q_db_count->fetch();
    _max_db_servers = fields[0].getUInt32();
    _gs_db = new MySQLDatabase*[_max_db_servers];
    for(uint i = 0; i < _max_db_servers; ++i)
        _gs_db[i] = NULL;
    do
    {
        fields = q_db_desc->fetch();
        db_id = fields[0].getUInt32();
        _gs_db[db_id] = new MySQLDatabase;
        bool res = _gs_db[db_id]->initialize ( fields[2].getString(), fields[3].getUInt32(), fields[4].getString(),
                                               fields[5].getString(), fields[1].getString(), 7, 16384 );
        if ( !res )
        {
            traceerr ( "SQL connection to db error. Server terminated." );
            exit ( 0 );
        }
    }
    while ( q_db_desc->nextRow() );
}
DatabaseManager::~ DatabaseManager()
{
    unlockDb(_pid);
    if ( _ss_db )
        delete _ss_db;
    for ( uint32 i = 0; i<_max_db_servers; i++ )
        if ( _gs_db[i] )
            delete _gs_db[i];
}

MySQLDatabase *DatabaseManager::getDatabase ( unsigned int id )
{
    if (id >= _max_db_servers)
        return NULL;
    return _gs_db[id];
}

MySQLDatabase *DatabaseManager::getSSDatabase()
{
    return _ss_db;
}
void DatabaseManager::lockDb ( string &work_dir, uint32 pid )
{
    _ss_db->query ( DB_LOCK_SQL__PID_WORK_PATH, pid, work_dir.c_str() );
}
bool DatabaseManager::testDb ( uint32 pid )
{
    Field *field;
    uint32 count_locked;
    shared_ptr<QueryResult> qres ( _ss_db->query ( DB_TEST_UNIQ_SQL__PID, pid ) );
    if ( !qres.get() )
        return false;
    do
    {
        field = qres->fetch();
        count_locked = field[0].getUInt32();
    }
    while ( qres->nextRow() );
    if ( count_locked > 1 )
    {
        traceerr ( "Error multiply server desc in DB config." );
        return false;
    }
    if ( count_locked == 0 )
    {
        traceerr ( "Error server allready running or not configured in DB config." );
        return false;
    }
    return true;
}
void DatabaseManager::unlockDb ( uint32 pid )
{
    _ss_db->query ( DB_UNLOCK_SQL__PID, pid );
}
