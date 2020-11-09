#include "mysql/MySQLBaseDaoTest.hpp"
#include "mysql/MySQLConnectionPool.hpp"
#include "user/NekoDeliveryUserDaoImpl.hpp"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}