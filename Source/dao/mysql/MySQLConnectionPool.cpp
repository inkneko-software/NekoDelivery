#include "MySQLConnectionPool.h"

void MySQLConnectionPool::prepareConnections() noexcept(false)
{
	for (int i = 0; i < maintainSize_; ++i)
	{
			sql::Connection* conn = ptrDriver->connect(host_, user_, password_);
			connpool.push_back(std::shared_ptr<sql::Connection>(conn));
	}
}

void MySQLConnectionPool::init(std::string host, unsigned short port, std::string user, std::string password, size_t maintainSize) noexcept(true)
{
	host_ = host;
	port_ = port;
	user_ = user;
	password_ = password;
	maintainSize_ = maintainSize;
}

PtrConnection MySQLConnectionPool::getConnection() noexcept(false)
{
	if (connpool.size() == 0)
	{
		try
		{
			prepareConnections();
		}
		catch (sql::SQLException& e)
		{
			if (connpool.size() == 0)
			{
				throw std::runtime_error(std::string("Failed to create connections, SQLErrorCode: ") + std::to_string(e.getErrorCode())
					+ std::string("SQLState: ") + e.getSQLState());
			}
			else
			{
				//ignore
			}
		}
	}

	PtrConnection conn(connpool.front());
	connpool.pop_front();
	return conn;
}

void MySQLConnectionPool::releaseConnection(PtrConnection conn) noexcept(true)
{
	try 
	{
		if (conn->isValid())
		{
			connpool.push_back(conn);
		}
	}
	catch (sql::SQLException& ignored) {}
}
