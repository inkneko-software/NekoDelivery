#pragma once
#include "MySQLConnectionPool.h"
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using PtrStatement = std::shared_ptr<sql::Statement>;
using PtrPreParedStatement = std::shared_ptr<sql::PreparedStatement>;
using PtrResultSet = std::shared_ptr<sql::ResultSet>;

class MySQLBaseDao
{
	MySQLConnectionPool pool;
public:
	MySQLBaseDao(std::string host, unsigned short port, std::string user, std::string password, size_t maintainSize)
	{
		pool.init(host, port, user, password, maintainSize);
	}

	PtrResultSet execueteQuery(std::string db, std::string st) noexcept(false);
};