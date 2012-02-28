#ifndef MYSQLDATABASE_H
#define MYSQLDATABASE_H

#include <mysql/mysql.h>
#include "database.h"
#include "common.h"

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

    bool initialize(const char* Hostname, unsigned int port,
                    const char* Username, const char* Password, const char* DatabaseName,
                    uint32 ConnectionCount, uint32 BufferSize);

    void shutdown();

    string escapeString(string Escape);
    void escapeLongString(const char* str, uint32 len, stringstream & out);
    string escapeString(const char* esc, DatabaseConnection* con);

    bool supportsReplaceInto() {
        return true;
    }
    bool supportsTableLocking() {
        return true;
    }

protected:    
    bool _handleError(MySQLDatabaseConnection*, uint32 ErrorNumber);
    bool _sendQuery(DatabaseConnection* con, const char* Sql, bool Self = false);

    void _beginTransaction(DatabaseConnection* conn);
    void _endTransaction(DatabaseConnection* conn);
    bool _reconnect(MySQLDatabaseConnection* conn);

    QueryResult* _storeQueryResult(DatabaseConnection* con);
};

class MySQLQueryResult : public QueryResult
{
public:
    MySQLQueryResult(MYSQL_RES* res, uint32 FieldCount, uint32 RowCount);
    ~MySQLQueryResult();

    bool nextRow();

protected:
    MYSQL_RES* mResult;
};

#endif // MYSQLDATABASE_H
