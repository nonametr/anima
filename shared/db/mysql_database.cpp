#include "mysql_database.h"
#include <iostream>
#include <sstream>

MySQLDatabase::~MySQLDatabase()
{
    for (int32 i = 0; i < mConnectionCount; ++i)
    {
        mysql_close(((MySQLDatabaseConnection*)Connections[i])->MySql);
        delete Connections[i];
    }
    delete [] Connections;
}

MySQLDatabase::MySQLDatabase() : Database()
{

}

void MySQLDatabase::_beginTransaction(DatabaseConnection* conn)
{
    _sendQuery(conn, "START TRANSACTION", false);
}

void MySQLDatabase::_endTransaction(DatabaseConnection* conn)
{
    _sendQuery(conn, "COMMIT", false);
}

bool MySQLDatabase::initialize(const char* Hostname, unsigned int port, const char* Username, const char* Password, const char* DatabaseName, uint32 ConnectionCount, uint32 BufferSize)
{
    uint32 i;
    MYSQL* temp = NULL;
    MYSQL* temp2 = NULL;
    MySQLDatabaseConnection** conns;
    my_bool my_true = true;

    mHostname = string(Hostname);
    mConnectionCount = ConnectionCount;
    mUsername = string(Username);
    mPassword = string(Password);
    mDatabaseName = string(DatabaseName);

    tracelog(OPTIMAL, "MySQLDatabase, connecting to `%s`, database `%s`...", Hostname, DatabaseName);

    conns = new MySQLDatabaseConnection*[ConnectionCount];
    Connections = ((DatabaseConnection**)conns);
    for (i = 0; i < ConnectionCount; ++i)
    {
        temp = mysql_init(NULL);
        if (temp == NULL)
            continue;

        if (mysql_options(temp, MYSQL_SET_CHARSET_NAME, "utf8"))
            traceerr("MySQLDatabase, could not set utf8 character set.");

        if (mysql_options(temp, MYSQL_OPT_RECONNECT, &my_true))
            traceerr("MySQLDatabase, MYSQL_OPT_RECONNECT could not be set, connection drops may occur but will be counteracted.");

        temp2 = mysql_real_connect(temp, Hostname, Username, Password, DatabaseName, port, NULL, 0);
        if (temp2 == NULL)
        {
            traceerr("MySQLDatabase, connection failed due to: `%s`", mysql_error(temp));
            mysql_close(temp);
            return false;
        }

        conns[i] = new MySQLDatabaseConnection;
        conns[i]->MySql = temp2;
    }

    Database::_initialize();
    return true;
}

string MySQLDatabase::escapeString(string Escape)
{
    char a2[16384] = { 0 };

    DatabaseConnection* con = getFreeConnection();
    string ret;
    if (mysql_real_escape_string(static_cast<MySQLDatabaseConnection*>(con)->MySql, a2, Escape.c_str(), (unsigned long)Escape.length()) == 0)
        ret = Escape.c_str();
    else
        ret = a2;

    con->Busy.unlock();

    return string(ret);
}

void MySQLDatabase::escapeLongString(const char* str, uint32 len, stringstream & out)
{
    char a2[65536 * 3] = { 0 };

    DatabaseConnection* con = getFreeConnection();

    mysql_real_escape_string(static_cast<MySQLDatabaseConnection*>(con)->MySql, a2, str, (unsigned long)len);

    out.write(a2, (std::streamsize)strlen(a2));
    con->Busy.unlock();
}

string MySQLDatabase::escapeString(const char* esc, DatabaseConnection* con)
{
    char a2[16384] = { 0 };
    const char* ret;
    if (mysql_real_escape_string(static_cast<MySQLDatabaseConnection*>(con)->MySql, a2, (char*)esc, (unsigned long)strlen(esc)) == 0)
        ret = esc;
    else
        ret = a2;

    return string(ret);
}

void MySQLDatabase::shutdown()
{
    mysql_library_end();
}

bool MySQLDatabase::_sendQuery(DatabaseConnection* con, const char* Sql, bool Self)
{
    //dunno what it does ...leaving untouched
    int result = mysql_query(static_cast<MySQLDatabaseConnection*>(con)->MySql, Sql);
    if (result > 0)
    {
        if (Self == false && _handleError(static_cast<MySQLDatabaseConnection*>(con), mysql_errno(static_cast<MySQLDatabaseConnection*>(con)->MySql)))
        {
            // Re-send the query, the connection was successful.
            // The true on the end will prevent an endless loop here, as it will
            // stop after sending the query twice.
            result = _sendQuery(con, Sql, true);
        }
        else
            traceerr("MySQLDatabase, Sql query failed due to [%s], Query: [%s]", mysql_error(static_cast<MySQLDatabaseConnection*>(con)->MySql), Sql);
    }

    return (result == 0 ? true : false);
}

bool MySQLDatabase::_handleError(MySQLDatabaseConnection* con, uint32 ErrorNumber)
{
    // Handle errors that should cause a reconnect to the Database.
    switch (ErrorNumber)
    {
    case 2006:  // Mysql server has gone away
    case 2008:  // Packet ran out of memory
    case 2013:  // Lost connection to sql server during query
    case 2055:  // Lost connection to sql server - system error
    {
        // Let's instruct a reconnect to the db when we encounter these errors.
        return _reconnect(con);
    }
    break;
    }

    return false;
}

MySQLQueryResult::MySQLQueryResult(MYSQL_RES* res, uint32 FieldCount, uint32 RowCount) : QueryResult(FieldCount, RowCount), mResult(res)
{
    mCurrentRow = new Field[FieldCount];
}

MySQLQueryResult::~MySQLQueryResult()
{
    mysql_free_result(mResult);
    delete [] mCurrentRow;
}

bool MySQLQueryResult::nextRow()
{
    MYSQL_ROW row = mysql_fetch_row(mResult);
    if (row == NULL)
        return false;

    for (uint32 i = 0; i < mFieldCount; ++i)
        mCurrentRow[i].setValue(row[i]);

    return true;
}

QueryResult* MySQLDatabase::_storeQueryResult(DatabaseConnection* con)
{
    MySQLQueryResult* res;
    MySQLDatabaseConnection* db = static_cast<MySQLDatabaseConnection*>(con);
    MYSQL_RES* pRes = mysql_store_result(db->MySql);
    uint32 uRows = (uint32)mysql_affected_rows(db->MySql);
    uint32 uFields = (uint32)mysql_field_count(db->MySql);

    if (uRows == 0 || uFields == 0 || pRes == 0)
    {
        if (pRes != NULL)
            mysql_free_result(pRes);

        return NULL;
    }

    res = new MySQLQueryResult(pRes, uFields, uRows);
    res->nextRow();

    return res;
}

bool MySQLDatabase::_reconnect(MySQLDatabaseConnection* conn)
{
    MYSQL* temp, *temp2;

    temp = mysql_init(NULL);
    temp2 = mysql_real_connect(temp, mHostname.c_str(), mUsername.c_str(), mPassword.c_str(), mDatabaseName.c_str(), mPort, NULL , 0);
    if (temp2 == NULL)
    {
        traceerr("MySQLDatabase, could not reconnect to database because of `%s`", mysql_error(temp));
        mysql_close(temp);
        return false;
    }

    if (conn->MySql != NULL)
        mysql_close(conn->MySql);

    conn->MySql = temp;
    return true;
}
