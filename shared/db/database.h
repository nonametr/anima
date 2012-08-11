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
    void addQuery(const char* format, ...);
    void perform();
    inline void setDB(Database* dbb) {
        db = dbb;
    }
};

class QueryBuffer
{
    vector<char*> queries;
public:
    friend class Database;
    void addQuery(const char* format, ...);
    void addQueryNA(const char* str);
    void addQueryStr(const string & str);
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
    void onShutdown() { _running = false; while(_running) sleep(1); };

    /************************************************************************/
    /* Virtual Functions                                                    */
    /************************************************************************/
    virtual bool initialize(const char* Hostname, unsigned int port,
                            const char* Username, const char* Password, const char* DatabaseName,
                            uint32 ConnectionCount, uint32 BufferSize) = 0;

    virtual void shutdown() = 0;

    virtual QueryResult* query(const char* QueryString, ...);
    virtual QueryResult* queryNA(const char* QueryString);
    virtual QueryResult* fQuery(const char* QueryString, DatabaseConnection* con);
    virtual void fWaitExecute(const char* QueryString, DatabaseConnection* con);
    virtual bool waitExecute(const char* QueryString, ...);//Wait For Request Completion
    virtual bool waitExecuteNA(const char* QueryString);//Wait For Request Completion
    virtual bool execute(const char* QueryString, ...);
    virtual bool executeNA(const char* QueryString);

    inline const string & getHostName() {
        return mHostname;
    }
    inline const string & getDatabaseName() {
        return mDatabaseName;
    }
    inline const uint32 getQueueSize() {
        return queries_queue.get_size();
    }

    virtual string escapeString(string Escape) = 0;
    virtual void escapeLongString(const char* str, uint32 len, stringstream & out) = 0;
    virtual string escapeString(const char* esc, DatabaseConnection* con) = 0;

    void queueAsyncQuery(AsyncQuery* query);
    void endThreads();

    void thread_proc_query(volatile bool &running);
    void freeQueryResult(QueryResult* p);

    DatabaseConnection* getFreeConnection();

    void performQueryBuffer(QueryBuffer* b, DatabaseConnection* ccon);
    void addQueryBuffer(QueryBuffer* b);

    static Database* createDatabaseInterface();
    static void cleanupLibs();

    virtual bool supportsReplaceInto() = 0;
    virtual bool supportsTableLocking() = 0;

protected:

    /// spawn threads and shizzle
    void _initialize();

    virtual void _beginTransaction(DatabaseConnection* conn) = 0;
    virtual void _endTransaction(DatabaseConnection* conn) = 0;

    /// actual query function
    virtual bool _sendQuery(DatabaseConnection* con, const char* Sql, bool Self) = 0;
    virtual QueryResult* _storeQueryResult(DatabaseConnection* con) = 0;

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

    virtual bool nextRow() = 0;
    void deleteThis() {
        delete this;
    }

    inline Field* fetch() {
        return mCurrentRow;
    }
    inline uint32 getFieldCount() const {
        return mFieldCount;
    }
    inline uint32 getRowCount() const {
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
    QueryThread(Database* d) : Thread(), db(d), _running(true){}
    ~QueryThread();
    void run();
    void onShutdown(){ _running = false; while(!_running){ sleep(1); } };
private:
    friend class Database;
    Database* db;
    volatile bool _running;
};
#endif // DATABASE_H
