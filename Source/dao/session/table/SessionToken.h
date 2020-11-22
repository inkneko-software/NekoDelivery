#pragma once
#include <string>

struct SessionToken
{
	unsigned long session_id;
	std::string   token;
	unsigned int  create_time;
	unsigned int  expire_time;
};