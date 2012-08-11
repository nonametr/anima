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
    DatabaseManager(string work_dir, uint32 pid);
    MySQLDatabase *getSSDatabase();
    MySQLDatabase *getDatabase(unsigned int id);
    virtual ~DatabaseManager();
private:
    void lockDb(string &work_dir, uint32 pid);
    bool testDb(uint32 pid);
    void unlockDb(uint32 pid);
    
    MySQLDatabase *_ss_db;
    MySQLDatabase **_gs_db;//max db = 10
    uint32 _pid;
    
    uint _max_db_servers;
};

#define iDBManager DatabaseManager::getSingletonPtr()

#endif // DATABASE_MANAGER_H
