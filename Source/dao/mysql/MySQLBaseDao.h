#pragma once
#include "MySQLConnectionPool.h"
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include <functional>

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

	bool execute(std::string db, std::string statement) noexcept(false);

	PtrResultSet execueteQuery(std::string db, std::string statement) noexcept(false);
	PtrResultSet execueteQuery(std::string db, std::string preparedStatement, std::function<void(PtrPreParedStatement pstm)> adapter) noexcept(false);

	size_t executeUpdate(std::string db, std::string statement) noexcept(false);
	size_t executeUpdate(std::string db, std::string statement, std::function<void(PtrPreParedStatement pstm)> adapter) noexcept(false);


};