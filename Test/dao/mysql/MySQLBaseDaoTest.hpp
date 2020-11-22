#pragma once
#include <gtest/gtest.h>
#include "../../../Source/dao/mysql/MySQLBaseDao.h"
#include <iostream>

TEST(MySQLbaseDaoTest, execute) {
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 1);
	EXPECT_EQ(1, 1);
}

TEST(MySQLbaseDaoTest, executeQuery) {
	MySQLBaseDao dao("127.0.0.1", 3306, "dev_leaf", "leaf", 10);
	PtrResultSet result = dao.executeQuery("test_db",
											"SELECT * FROM test_table WHERE id=?",
											[](PtrPreparedStatement ptsm) {
													ptsm->setInt(1, 1); });
	result->next();
	EXPECT_EQ(1, result->getInt(1));
	EXPECT_EQ("leaf", result->getString(2));
}

TEST(MySQLbaseDaoTest, executePreparedQuery) {
	EXPECT_EQ(1, 1);
}

TEST(MySQLbaseDaoTest, executeUpdate) {
	EXPECT_EQ(1, 1);
}

TEST(MySQLbaseDaoTest, executePreparedUpdate) {
	EXPECT_EQ(1, 1);
}