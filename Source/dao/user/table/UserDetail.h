#pragma once
#include <string>
struct UserDetail
{
	unsigned int uid;
	unsigned long phone;
	std::string nick;
	std::string name;
	std::string avatar;
	long register_date;
	short state;
};