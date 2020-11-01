#pragma once
#include <list>
#include <memory>
#include <string>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <mysql_driver.h>

using PtrConnection = std::shared_ptr<sql::Connection>;
class MySQLConnectionPool
{
	sql::Driver* ptrDriver;
	std::list<PtrConnection> connpool;

	std::string host_; 
	unsigned short port_; 
	std::string user_; 
	std::string password_;
	size_t maintainSize_;

	void prepareConnections() noexcept(false);
public:
	MySQLConnectionPool() : ptrDriver(sql::mysql::get_driver_instance()) {}


	void init(std::string host, unsigned short port, std::string user, std::string password, size_t maintainSize) noexcept(true);

	PtrConnection getConnection() noexcept(false);

	void releaseConnection(PtrConnection conn) noexcept(true);
};