#pragma once
#include <string>

struct CouriersInfo
{
	unsigned int uid;
	std::string passport_front;
	std::string passport_detail;
	unsigned int operator_id;
	long accept_date;
};