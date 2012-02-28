#include "database_manager.h"

initialiseSingleton ( DatabaseManager );

DatabaseManager::DatabaseManager()
{
    int db_id;
    Field *fields;
    ss_db = new MySQLDatabase;
    bool res = ss_db->initialize(iConfig->getParam(Config::SSD_IP).c_str(), iConfig->getParam(Config::SSD_PORT), iConfig->getParam(Config::SSD_USER).c_str(), iConfig->getParam(Config::SSD_PASSWORD).c_str(), iConfig->getParam(Config::SSD_NAME).c_str(), 2, 16384);
    if (!res)
    {
        traceerr("SQL connection to ss_db error. Server terminated.");
        exit(0);
    }
    shared_ptr<QueryResult> q_db_count(ss_db->queryNA(DB_GET_COUNT));
    shared_ptr<QueryResult> q_db_desc(ss_db->queryNA(DB_GET_DESC));

    if (!q_db_count.get() || !q_db_desc.get())
    {
        traceerr("Error fetching db desc data!");
        return;
    }
    fields = q_db_count->fetch();
    _max_db_servers = fields[0].getUInt32();
    gs_db = new MySQLDatabase*[_max_db_servers];
    do {
        fields = q_db_desc->fetch();
        db_id = fields[0].getUInt32();
        gs_db[db_id] = new MySQLDatabase;
        bool res = gs_db[db_id]->initialize(fields[2].getString(), fields[3].getUInt32(), fields[4].getString(), fields[5].getString(), fields[1].getString(), 7, 16384);
        if (!res)
        {
            traceerr("SQL connection to db error. Server terminated.");
            exit(0);
        }
    } while (q_db_desc->nextRow());
}
DatabaseManager::~ DatabaseManager()
{
    for (uint32 i = 0; i<_max_db_servers; i++)
    {
        delete gs_db[i];
    }
}

MySQLDatabase *DatabaseManager::getDatabase(unsigned int id)
{
    return gs_db[id];
}

MySQLDatabase *DatabaseManager::getSSDatabase()
{
    return ss_db;
}
