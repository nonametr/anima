#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H
#include "../shared/singleton.h"
#include "../shared/db/database.h"
#include "../shared/db/mysql_database.h"
#include "../shared/config.h"
#include "../shared/common.h"

#define GET_DB_DESC "SELECT db_id, name, ip, port, user, password, charset FROM db_desc WHERE active = 1"
#define GET_DB_COUNT "SELECT MAX(db_id)+1 FROM db_desc WHERE active = 1"

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
};

#define iDBManager DatabaseManager::getSingletonPtr()

#endif // DATABASE_MANAGER_H
