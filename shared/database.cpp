#include "database.h"
#include <stdio.h>
#include <stdarg.h>

SQLCallbackBase::~SQLCallbackBase()
{

}

Database::Database() : Thread()
{
	_counter = 0;
	Connections = NULL;
	mConnectionCount = -1;   // Not connected.
	_running = true;
}

Database::~Database()
{

}

void Database::_Initialize()
{
	// Spawn Database thread
	iThreadCore->startThread(this);

	// launch the query thread
	qt = new QueryThread(this);
	iThreadCore->startThread(qt);
}

DatabaseConnection* Database::GetFreeConnection()
{
	uint32 i = 0;
	for(;;)
	{
		DatabaseConnection* con = Connections[((i++) % mConnectionCount) ];
		if(con->Busy.try_lock())
			return con;
	}

	// shouldn't be reached
	return NULL;
}

// Use this when we request data that can return a value (not async)
QueryResult* Database::Query(const char* QueryString, ...)
{
	char sql[16384];
	va_list vlist;
	va_start(vlist, QueryString);
	vsnprintf(sql, 16384, QueryString, vlist);
	va_end(vlist);

	// Send the query
	QueryResult* qResult = NULL;
	DatabaseConnection* con = GetFreeConnection();

	if(_SendQuery(con, sql, false))
		qResult = _StoreQueryResult(con);

	con->Busy.unlock();
	return qResult;
}

QueryResult* Database::QueryNA(const char* QueryString)
{
	// Send the query
	QueryResult* qResult = NULL;
	DatabaseConnection* con = GetFreeConnection();

	if(_SendQuery(con, QueryString, false))
		qResult = _StoreQueryResult(con);

	con->Busy.unlock();
	return qResult;
}

QueryResult* Database::FQuery(const char* QueryString, DatabaseConnection* con)
{
	// Send the query
	QueryResult* qResult = NULL;
	if(_SendQuery(con, QueryString, false))
		qResult = _StoreQueryResult(con);

	return qResult;
}

void Database::FWaitExecute(const char* QueryString, DatabaseConnection* con)
{
	// Send the query
	_SendQuery(con, QueryString, false);
}

void QueryBuffer::AddQuery(const char* format, ...)
{
	char query[16384];
	va_list vlist;
	va_start(vlist, format);
	vsnprintf(query, 16384, format, vlist);
	va_end(vlist);

	size_t len = strlen(query);
	char* pBuffer = new char[len + 1];
	memcpy(pBuffer, query, len + 1);

	queries.push_back(pBuffer);
}

void QueryBuffer::AddQueryNA(const char* str)
{
	size_t len = strlen(str);
	char* pBuffer = new char[len + 1];
	memcpy(pBuffer, str, len + 1);

	queries.push_back(pBuffer);
}

void QueryBuffer::AddQueryStr(const string & str)
{
	size_t len = str.size();
	char* pBuffer = new char[len + 1];
	memcpy(pBuffer, str.c_str(), len + 1);

	queries.push_back(pBuffer);
}

void Database::PerformQueryBuffer(QueryBuffer* b, DatabaseConnection* ccon)
{
	if(!b->queries.size())
		return;

	DatabaseConnection* con = ccon;
	if(ccon == NULL)
		con = GetFreeConnection();

	_BeginTransaction(con);

	for(vector<char*>::iterator itr = b->queries.begin(); itr != b->queries.end(); ++itr)
	{
		_SendQuery(con, *itr, false);
		delete[](*itr);
	}

	_EndTransaction(con);

	if(ccon == NULL)
		con->Busy.unlock();
}
// Use this when we do not have a result. ex: INSERT into SQL 1
bool Database::Execute(const char* QueryString, ...)
{
	char query[16384];

	va_list vlist;
	va_start(vlist, QueryString);
	vsnprintf(query, 16384, QueryString, vlist);
	va_end(vlist);

	if(!_running)
		return WaitExecuteNA(query);

	size_t len = strlen(query);
	char* pBuffer = new char[len + 1];
	memcpy(pBuffer, query, len + 1);

	queries_queue.push(pBuffer);
	return true;
}

bool Database::ExecuteNA(const char* QueryString)
{
	if(!_running)
		return WaitExecuteNA(QueryString);

	size_t len = strlen(QueryString);
	char* pBuffer = new char[len + 1];
	memcpy(pBuffer, QueryString, len + 1);

	queries_queue.push(pBuffer);
	return true;
}

// Wait till the other queries are done, then execute
bool Database::WaitExecute(const char* QueryString, ...)
{
	char sql[16384];
	va_list vlist;
	va_start(vlist, QueryString);
	vsnprintf(sql, 16384, QueryString, vlist);
	va_end(vlist);

	DatabaseConnection* con = GetFreeConnection();
	bool Result = _SendQuery(con, sql, false);
	con->Busy.unlock();
	return Result;
}

bool Database::WaitExecuteNA(const char* QueryString)
{
	DatabaseConnection* con = GetFreeConnection();
	bool Result = _SendQuery(con, QueryString, false);
	con->Busy.unlock();
	return Result;
}

void Database::run()
{
	_running = true;
	char* query = queries_queue.pop();
	DatabaseConnection* con = GetFreeConnection();
	while(1)
	{

		if(query != NULL)
		{
			if(con == NULL)
				con = GetFreeConnection();
			_SendQuery(con, query, false);
			delete[] query;
		}

		if(!_running)
			break;
		query = queries_queue.pop();

		if(query == NULL)
		{
			if(con != NULL)
				con->Busy.unlock();
			con = NULL;
			sleep(5);
		}
	}

	if(con != NULL)
		con->Busy.unlock();

	// execute all the remaining queries
	query = queries_queue.pop();
	while(query)
	{
		con = GetFreeConnection();
		_SendQuery(con, query, false);
		con->Busy.unlock();
		delete[] query;
		query = queries_queue.pop();
	}

	_running = false;
}

void AsyncQuery::AddQuery(const char* format, ...)
{
	AsyncQueryResult res;
	va_list ap;
	char buffer[10000];
	size_t len;
	va_start(ap, format);
	vsnprintf(buffer, 10000, format, ap);
	va_end(ap);
	len = strlen(buffer);
	ASSERT(len);
	res.query = new char[len + 1];
	res.query[len] = 0;
	memcpy(res.query, buffer, len);
	res.result = NULL;
	queries.push_back(res);
}

void AsyncQuery::Perform()
{
	DatabaseConnection* conn = db->GetFreeConnection();
	for(vector<AsyncQueryResult>::iterator itr = queries.begin(); itr != queries.end(); ++itr)
		itr->result = db->FQuery(itr->query, conn);

	conn->Busy.unlock();
	func->run(queries);

	delete this;
}

AsyncQuery::~AsyncQuery()
{
	delete func;
	for(vector<AsyncQueryResult>::iterator itr = queries.begin(); itr != queries.end(); ++itr)
	{
		if(itr->result)
			delete itr->result;

		delete[] itr->query;
	}
}

void Database::EndThreads()
{
	//these 2 loops spin until theres nothing left
	while(1)
	{
		QueryBuffer* buf = query_buffer.pop();
		if(buf == NULL)
			break;
		query_buffer.push(buf);
	}
	while(1)
	{
		char* buf = queries_queue.pop();
		if(buf == NULL)
			break;
		queries_queue.push(buf);
	}

	_running = false;

	while(_running || qt)
	{
		sleep(1);
		if(!_running)
			break;
	}
}

void QueryThread::run()
{
	db->thread_proc_query();
}

QueryThread::~QueryThread()
{
	db->qt = NULL;
}

void Database::thread_proc_query()
{
	QueryBuffer* q;
	DatabaseConnection* con = GetFreeConnection();

	q = query_buffer.pop();
	while(1)
	{
		if(q != NULL)
		{
			PerformQueryBuffer(q, con);
			delete q;
		}

		if(!_running)
			break;

		q = query_buffer.pop();
		if(q == NULL)
			sleep(5);
	}

	con->Busy.unlock();

	// kill any queries
	q = query_buffer.pop();
	while(q != NULL)
	{
		PerformQueryBuffer(q, NULL);
		delete q;

		q = query_buffer.pop();
	}
}

void Database::QueueAsyncQuery(AsyncQuery* query)
{
	query->db = this;
	/*if(qt == NULL)
	{
		query->Perform();
		return;
	}

	qqueries_queue.push(query);*/
	query->Perform();
}

void Database::AddQueryBuffer(QueryBuffer* b)
{
	if(qt != NULL)
		query_buffer.push(b);
	else
	{
		PerformQueryBuffer(b, NULL);
		delete b;
	}
}

void Database::FreeQueryResult(QueryResult* p)
{
	delete p;
}
