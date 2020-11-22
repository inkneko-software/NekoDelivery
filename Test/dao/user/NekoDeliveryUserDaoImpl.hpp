#pragma once
#include <gtest/gtest.h>
#include "../../../Source/dao/user/impl/NekoDeliveryUserDaoImpl.h"
#include <iostream>
TEST(NekoDeliveryUserDaoImplTest, registerTest) {
	NekoDeliveryUserDao* userDao = new NekoDeliveryUserDaoImpl("127.0.0.1", 3306, "dev_leaf", "leaf", 10);

	/*UserDetail detail = {};
	detail.avatar = "default.jpg";
	detail.name = u8"未实名";
	detail.nick = u8"罗小黑";
	detail.phone = 1701234123;
	detail.state = 0;
	detail.register_date = 114514;

	UserAuth userAuth = {};
	userAuth.uid = 1;
	userAuth.auth_hash = "HAHAHAHAHA-afehaef=asd";
	userAuth.auth_salt = "hahahahahahahahaha";
	userAuth.phone = 1701234123;
	userAuth.update_date = 114514;
	userDao->registerAccount(detail, userAuth);
	*/
	auto result = userDao->getUserDetailByUid(2);	
	EXPECT_EQ(2, result->uid);
	using namespace std;
	cout << result->uid << endl;
	cout << result->nick << endl;
	EXPECT_STREQ(std::string(u8"罗小黑").c_str(), result->nick.c_str());
 }
