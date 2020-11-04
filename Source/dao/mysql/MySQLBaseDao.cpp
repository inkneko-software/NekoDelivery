#include "MySQLBaseDao.h"

bool MySQLBaseDao::execute(std::string db, std::string statement) noexcept(false)
{
	PtrConnection conn(pool.getConnection());
	try
	{
		conn->setSchema(db);
		PtrStatement querySt(conn->createStatement());
		bool ret = querySt->execute(statement);
		pool.releaseConnection(conn);
		return ret;
	}
	catch (sql::SQLException& e)
	{
		pool.releaseConnection(conn);
		throw e;
	}
}
PtrResultSet MySQLBaseDao::executeQuery(std::string db, std::string st) noexcept(false)
{
	PtrConnection conn(pool.getConnection());
	try 
	{
		conn->setSchema(db);
		PtrStatement querySt(conn->createStatement());
		PtrResultSet result(querySt->executeQuery(st));
		pool.releaseConnection(conn);
		return result;
	}
	catch (sql::SQLException& e)
	{
		pool.releaseConnection(conn);
		throw e;
	}
}

PtrResultSet MySQLBaseDao::executeQuery(std::string db, std::string preparedStatement, std::function<void(PtrPreParedStatement pstm)> adapter) noexcept(false)
{
	PtrConnection conn(pool.getConnection());
	try
	{
		conn->setSchema(db);
		PtrPreParedStatement querySt(conn->prepareStatement(preparedStatement));
		adapter(querySt);
		PtrResultSet result(querySt->executeQuery());
		pool.releaseConnection(conn);
		return result;
	}
	catch (sql::SQLException& e)
	{
		pool.releaseConnection(conn);
		throw e;
	}
}

size_t MySQLBaseDao::executeUpdate(std::string db, std::string statement) noexcept(false)
{
	PtrConnection conn(pool.getConnection());
	try
	{
		conn->setSchema(db);
		PtrStatement querySt(conn->createStatement());
		size_t affected = querySt->executeUpdate(statement);
		pool.releaseConnection(conn);
		return affected;
	}
	catch (sql::SQLException& e)
	{
		pool.releaseConnection(conn);
		throw e;
	}
}
size_t MySQLBaseDao::executeUpdate(std::string db, std::string preparedStatement, std::function<void(PtrPreParedStatement pstm)> adapter) noexcept(false)
{
	PtrConnection conn(pool.getConnection());
	try
	{
		conn->setSchema(db);
		PtrPreParedStatement querySt(conn->prepareStatement(preparedStatement));
		adapter(querySt);
		size_t affected = querySt->executeUpdate();
		pool.releaseConnection(conn);
		return affected;
	}
	catch (sql::SQLException& e)
	{
		pool.releaseConnection(conn);
		throw e;
	}
}