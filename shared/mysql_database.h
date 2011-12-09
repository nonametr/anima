#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include <mysql/mysql.h>
#include "database.h"

struct MySQLDatabaseConnection : public DatabaseConnection
{
    MYSQL* MySql;
};

class MySQLDatabase : public Database
{
    friend class QueryThread;
    friend class AsyncQuery;
public:
    MySQLDatabase();
    ~MySQLDatabase();

    bool Initialize(const char* Hostname, unsigned int port,
                    const char* Username, const char* Password, const char* DatabaseName,
                    uint32 ConnectionCount, uint32 BufferSize);

    void Shutdown();

    string EscapeString(string Escape);
    void EscapeLongString(const char* str, uint32 len, stringstream & out);
    string EscapeString(const char* esc, DatabaseConnection* con);

    bool SupportsReplaceInto() {
        return true;
    }
    bool SupportsTableLocking() {
        return true;
    }

protected:

    bool _HandleError(MySQLDatabaseConnection*, uint32 ErrorNumber);
    bool _SendQuery(DatabaseConnection* con, const char* Sql, bool Self = false);

    void _BeginTransaction(DatabaseConnection* conn);
    void _EndTransaction(DatabaseConnection* conn);
    bool _Reconnect(MySQLDatabaseConnection* conn);

    QueryResult* _StoreQueryResult(DatabaseConnection* con);
};

class MySQLQueryResult : public QueryResult
{
public:
    MySQLQueryResult(MYSQL_RES* res, uint32 FieldCount, uint32 RowCount);
    ~MySQLQueryResult();

    bool NextRow();

protected:
    MYSQL_RES* mResult;
};

#endif // MYSQLDATABASE_H
