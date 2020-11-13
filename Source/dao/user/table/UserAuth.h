#pragma once
#include <string>
struct UserAuth
{
	unsigned int uid;
	unsigned long phone;
	std::string auth_salt;
	std::string auth_hash;
	long update_date;
};