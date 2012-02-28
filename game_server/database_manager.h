#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H
#include "singleton.h"
#include "database.h"
#include "mysql_database.h"
#include "config.h"
#include "common.h"
#include "sql_define.h"

class DatabaseManager : public Singleton<DatabaseManager>
{
public:
    DatabaseManager();
    MySQLDatabase *getSSDatabase();
    MySQLDatabase *getDatabase(unsigned int id);
    virtual ~DatabaseManager();
private:
    MySQLDatabase *ss_db;
    MySQLDatabase **gs_db;//max db = 10
    
    uint _max_db_servers;
};

#define iDBManager DatabaseManager::getSingletonPtr()

#endif // DATABASE_MANAGER_H
