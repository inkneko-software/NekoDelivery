#include "MySQLBaseDao.h"


sql::ResultSet* MySQLBaseDao::execueteQuery(std::string db, std::string st) noexcept(false)
{
	PtrConnection conn(pool.getConnection());
	conn->setSchema(db);
	sql::Statement* querySt = conn->createStatement();
	sql::ResultSet* ret = querySt->executeQuery(st);

	pool.releaseConnection(conn);
	return ret;
}