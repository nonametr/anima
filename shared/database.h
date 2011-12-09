#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "thread.h"
#include "common.h"
#include "callback.h"
#include "field.h"
#include "thread_core.h"

using namespace std;
class QueryResult;
class QueryThread;
class Database;

struct DatabaseConnection
{
    Mutex Busy;
};

struct AsyncQueryResult
{
    QueryResult* result;
    char* query;
};

class AsyncQuery
{
    friend class Database;
    SQLCallbackBase* func;
    vector<AsyncQueryResult> queries;
    Database* db;
public:
    AsyncQuery(SQLCallbackBase* f) : func(f) {}
    ~AsyncQuery();
    void AddQuery(const char* format, ...);
    void Perform();
    inline void SetDB(Database* dbb) {
        db = dbb;
    }
};

class QueryBuffer
{
    vector<char*> queries;
public:
    friend class Database;
    void AddQuery(const char* format, ...);
    void AddQueryNA(const char* str);
    void AddQueryStr(const string & str);
};

class Database : public Thread
{
    friend class QueryThread;
    friend class AsyncQuery;
public:
    Database();
    virtual ~Database();

    /************************************************************************/
    /* Thread Stuff                                                         */
    /************************************************************************/
    void run();
    void onShutdown() { _running = false; };

    /************************************************************************/
    /* Virtual Functions                                                    */
    /************************************************************************/
    virtual bool Initialize(const char* Hostname, unsigned int port,
                            const char* Username, const char* Password, const char* DatabaseName,
                            uint32 ConnectionCount, uint32 BufferSize) = 0;

    virtual void Shutdown() = 0;

    virtual QueryResult* Query(const char* QueryString, ...);
    virtual QueryResult* QueryNA(const char* QueryString);
    virtual QueryResult* FQuery(const char* QueryString, DatabaseConnection* con);
    virtual void FWaitExecute(const char* QueryString, DatabaseConnection* con);
    virtual bool WaitExecute(const char* QueryString, ...);//Wait For Request Completion
    virtual bool WaitExecuteNA(const char* QueryString);//Wait For Request Completion
    virtual bool Execute(const char* QueryString, ...);
    virtual bool ExecuteNA(const char* QueryString);

    inline const string & GetHostName() {
        return mHostname;
    }
    inline const string & GetDatabaseName() {
        return mDatabaseName;
    }
    inline const uint32 GetQueueSize() {
        return queries_queue.get_size();
    }

    virtual string EscapeString(string Escape) = 0;
    virtual void EscapeLongString(const char* str, uint32 len, stringstream & out) = 0;
    virtual string EscapeString(const char* esc, DatabaseConnection* con) = 0;

    void QueueAsyncQuery(AsyncQuery* query);
    void EndThreads();

    void thread_proc_query();
    void FreeQueryResult(QueryResult* p);

    DatabaseConnection* GetFreeConnection();

    void PerformQueryBuffer(QueryBuffer* b, DatabaseConnection* ccon);
    void AddQueryBuffer(QueryBuffer* b);

    static Database* CreateDatabaseInterface();
    static void CleanupLibs();

    virtual bool SupportsReplaceInto() = 0;
    virtual bool SupportsTableLocking() = 0;

protected:

    // spawn threads and shizzle
    void _Initialize();

    virtual void _BeginTransaction(DatabaseConnection* conn) = 0;
    virtual void _EndTransaction(DatabaseConnection* conn) = 0;

    // actual query function
    virtual bool _SendQuery(DatabaseConnection* con, const char* Sql, bool Self) = 0;
    virtual QueryResult* _StoreQueryResult(DatabaseConnection* con) = 0;

    ////////////////////////////////
    FQueue<QueryBuffer*> query_buffer;

    ////////////////////////////////
    FQueue<char*> queries_queue;
    DatabaseConnection** Connections;

    uint32 _counter;
    volatile bool _running;
    ///////////////////////////////

    int32 mConnectionCount;

    // For reconnecting a broken connection
    string mHostname;
    string mUsername;
    string mPassword;
    string mDatabaseName;
    uint32 mPort;

    QueryThread* qt;
};

class QueryResult
{
public:
    QueryResult(uint32 fields, uint32 rows) : mFieldCount(fields), mRowCount(rows), mCurrentRow(NULL) {}
    virtual ~QueryResult() {}

    virtual bool NextRow() = 0;
    void Delete() {
        delete this;
    }

    inline Field* Fetch() {
        return mCurrentRow;
    }
    inline uint32 GetFieldCount() const {
        return mFieldCount;
    }
    inline uint32 GetRowCount() const {
        return mRowCount;
    }

protected:
    uint32 mFieldCount;
    uint32 mRowCount;
    Field* mCurrentRow;
};

class QueryThread : public Thread
{
public:
    QueryThread(Database* d) : Thread(), db(d) {}
    ~QueryThread();
    void run();
    void onShutdown(){ _running = false; };
private:
    friend class Database;
    Database* db;
    volatile bool _running;
};
#endif // DATABASE_H
