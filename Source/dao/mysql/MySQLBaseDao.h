#pragma once
#include "MySQLConnectionPool.h"
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
class MySQLBaseDao
{
	MySQLConnectionPool pool;
public:
	MySQLBaseDao(std::string host, unsigned short port, std::string user, std::string password, size_t maintainSize)
	{
		pool.init(host, port, user, password, maintainSize);
	}

	sql::ResultSet* execueteQuery(std::string db, std::string st) noexcept(false);
};