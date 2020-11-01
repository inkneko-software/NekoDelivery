#include "MySQLBaseDao.h"


PtrResultSet MySQLBaseDao::execueteQuery(std::string db, std::string st) noexcept(false)
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