#include "NekoDeliveryAuth.h"
#include <tinyHttpd/webstring.h>
#include <nlohmann/json.hpp>
#include <boost/regex.hpp>
#include <ctime>

#include <iostream>


NekoDeliveryAuth::NekoDeliveryAuth()
{
	userDao.reset(new NekoDeliveryUserDaoImpl("127.0.0.1", 3306, "dev_leaf", "leaf", 10));
	sessionManager.reset(new NekoDeliverySession());

	routeTable[apiPrefix + "/checkPhone"]      = ROUTE_CALLBACK{ return this->checkPhone(request); };
	routeTable[apiPrefix + "/sendRegisterSMG"] = ROUTE_CALLBACK{ return this->sendRegisterSMG(request); };
	routeTable[apiPrefix + "/sendRecoverSMG"]  = ROUTE_CALLBACK{ return this->sendRecoverSMG(request); };
	routeTable[apiPrefix + "/registerAccount"] = ROUTE_CALLBACK{ return this->registerAccount(request); };
	routeTable[apiPrefix + "/loginAccount"]    = ROUTE_CALLBACK{ return this->loginAccount(request); };
	routeTable[apiPrefix + "/resetPassword"]   = ROUTE_CALLBACK{ return this->resetPassword(request); };
	routeTable[apiPrefix + "/updateDetail"]    = ROUTE_CALLBACK{ return this->updateDetail(request); };

}

void NekoDeliveryAuth::HTTPPacketHandler(int clientfd, HTTPPacket::HTTPRequestPacket request) noexcept
{
	HTTPPacket::HTTPResponsePacket response;
	auto route = routeTable.find(request.requestPath);
	if (route != routeTable.end())
	{
		response = route->second(clientfd, request);
	}
	else
	{
		response.SetResponseCode(HTTPPacket::ResponseCode::NotFound);
	}
	connectedClients[clientfd].writeBuffer += response.ToString();
}

HTTPPacket::HTTPResponsePacket NekoDeliveryAuth::checkPhone(HTTPPacket::HTTPRequestPacket request) noexcept
{
	HTTPPacket::HTTPResponsePacket response;
	response.SetResponseCode(HTTPPacket::ResponseCode::OK);
	response.SetContentType("application/json; charset=utf8");
	
	nlohmann::json responseJson;
	auto requestParam = webstring::ParseKeyValue(request.body);
	if (checkPhoneFormat(requestParam["phone"]) == false) {
		responseJson["code"] = -10001;
		responseJson["msg"] = "手机号码格式错误";
		response.body = responseJson.dump();
		return response;
	}

	try
	{
		long phone = std::stol(requestParam["phone"]);
		auto result =  userDao->getUserDetailByPhone(phone);
		if (result != nullptr)
		{
			responseJson["code"] = -10002;
			responseJson["msg"] = "手机号码已被注册";
		}
		else
		{
			responseJson["code"] = 0;
			responseJson["msg"] = "手机号码可以注册";
		}
	}
	catch (const std::exception& e)
	{
		response.SetResponseCode(HTTPPacket::ResponseCode::InternalServerError);
		responseJson["code"] = -10500;
		responseJson["msg"] = "Server Internal Error";
		std::cout << e.what() << std::endl;
	}
	response.body = responseJson.dump();
	return response;
}

HTTPPacket::HTTPResponsePacket NekoDeliveryAuth::sendRegisterSMG(HTTPPacket::HTTPRequestPacket request) noexcept
{
	HTTPPacket::HTTPResponsePacket response;
	response.SetResponseCode(HTTPPacket::ResponseCode::OK);
	response.SetContentType("application/json; charset=utf8");

	nlohmann::json responseJson;
	auto requestParam = webstring::ParseKeyValue(request.body);
	if (checkPhoneFormat(requestParam["phone"]) == false) {
		responseJson["code"] = -10001;
		responseJson["msg"] = "手机号码格式错误";
		response.body = responseJson.dump();
		return response;
	}

	try
	{
		long phone = std::stol(requestParam["phone"]);
		auto result = userDao->getUserDetailByPhone(phone);
		if (result != nullptr)
		{
			responseJson["code"] = -10002;
			responseJson["msg"] = "手机号码已被注册";
		}
		else
		{
			AccessCode ac;
			ac.ctime = time(nullptr);
			ac.phone = std::stol(requestParam["phone"]);
			ac.vcode = "123456"; //mock
			userDao->saveAccessCode(ac);

			//call smg sender service...
			//...
			responseJson["code"] = 0;
			responseJson["msg"] = "注册验证码发送成功";
		}
	}
	catch (const std::exception& e)
	{
		response.SetResponseCode(HTTPPacket::ResponseCode::InternalServerError);
		responseJson["code"] = -10500;
		responseJson["msg"] = "Server Internal Error";
		std::cout << e.what() << std::endl;
	}
	response.body = responseJson.dump();
	return response;
}

HTTPPacket::HTTPResponsePacket NekoDeliveryAuth::sendRecoverSMG(HTTPPacket::HTTPRequestPacket request) noexcept
{
	HTTPPacket::HTTPResponsePacket response;
	response.SetResponseCode(HTTPPacket::ResponseCode::OK);
	response.SetContentType("application/json; charset=utf8");

	nlohmann::json responseJson;
	auto requestParam = webstring::ParseKeyValue(request.body);
	if (checkPhoneFormat(requestParam["phone"]) == false) {
		responseJson["code"] = -10001;
		responseJson["msg"] = "手机号码格式错误";
		response.body = responseJson.dump();
		return response;
	}

	try
	{
		long phone = std::stol(requestParam["phone"]);
		auto result = userDao->getUserDetailByPhone(phone);
		if (result  == nullptr)
		{
			responseJson["code"] = -10003;
			responseJson["msg"] = "手机号码未注册";
		}
		else
		{
			RecoverCode rc;
			rc.ctime = time(nullptr);
			rc.phone = std::stol(requestParam["phone"]);
			rc.vcode = "234567"; //mock
			userDao->saveRecoverCode(rc);

			//call smg sender service...
			//...
			responseJson["code"] = 0;
			responseJson["msg"] = "重置验证码发送成功";
		}
	}
	catch (const std::exception& e)
	{
		response.SetResponseCode(HTTPPacket::ResponseCode::InternalServerError);
		responseJson["code"] = -10500;
		responseJson["msg"] = "Server Internal Error";
		std::cout << e.what() << std::endl;
	}
	response.body = responseJson.dump();
	return response;
}

HTTPPacket::HTTPResponsePacket NekoDeliveryAuth::registerAccount(HTTPPacket::HTTPRequestPacket request) noexcept
{
	HTTPPacket::HTTPResponsePacket response;
	response.SetResponseCode(HTTPPacket::ResponseCode::OK);
	response.SetContentType("application/json; charset=utf8");

	nlohmann::json responseJson;
	auto requestParam = webstring::ParseKeyValue(request.body);
	if (checkPhoneFormat(requestParam["phone"]) == false)
	{
		responseJson["code"] = -10001;
		responseJson["msg"] = "手机号码格式错误";
		response.body = responseJson.dump();
		return response;
	}
	if (checkPasswordFormat(requestParam["password"]) == false)
	{
		responseJson["code"] = -10004;
		responseJson["msg"] = "密码格式错误";
		response.body = responseJson.dump();
		return response;
	}
	size_t nameLen = webstring::UTF8Strlen(webstring::URLdecode(requestParam["name"]));
	std::cout << nameLen << std::endl;
	if (nameLen < 2 || nameLen > 15)
	{
		responseJson["code"] = -10008;
		responseJson["msg"] = "姓名长度不符合要求";
		response.body = responseJson.dump();
		return response;
	}
	size_t nickLen = webstring::UTF8Strlen(webstring::URLdecode(requestParam["nick"]));
	if (nickLen < 2 || nickLen > 15)
	{
		responseJson["code"] = -10009;
		responseJson["msg"] = "昵称长度不符合要求";
		response.body = responseJson.dump();
		return response;
	}

	try
	{
		long phone = std::stol(requestParam["phone"]);
		auto result = userDao->getUserDetailByPhone(phone);
		if (result  != nullptr)
		{
			responseJson["code"] = -10002;
			responseJson["msg"] = "手机号码已被注册";
		}
		else
		{
			std::string vcode = requestParam["vcode"];
			time_t currentTime = time(nullptr);
			auto ret = userDao->getAccessCode(std::stol(requestParam["phone"]), 1);
			bool found = false;
			for (auto accessCode : ret)
			{
				if (currentTime - accessCode.ctime < 5 * 60 * 1000 && vcode == accessCode.vcode)
				{
					found = true;
					break;
				}
			}
			if (found == false)
			{
				responseJson["code"] = -10007;
				responseJson["msg"] = "注册验证码错误";
			}
			else
			{
				UserDetail userDetail;
				UserAuth userAuth;
				userDetail.avatar = "/default.jpg";
				userDetail.name = webstring::URLdecode(requestParam["name"]);
				userDetail.nick = webstring::URLdecode(requestParam["nick"]);
				userDetail.phone = std::stol(requestParam["phone"]);
				userDetail.register_date = time(nullptr);
				userDetail.state = 0;

				userAuth.auth_salt = webstring::GenUUID() + webstring::GenTimeStamp();
				userAuth.auth_hash = webstring::sha1(requestParam["password"]);
				userAuth.auth_hash = webstring::sha1(userAuth.auth_salt + userAuth.auth_hash);
				userAuth.phone = userDetail.phone;
				userAuth.update_date = userDetail.register_date;

				if (userDao->registerAccount(userDetail, userAuth))
				{
					responseJson["code"] = 0;
					responseJson["msg"] = "注册成功";
				}
				else
				{
					responseJson["code"] = -10006;
					responseJson["msg"] = "注册失败";
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		response.SetResponseCode(HTTPPacket::ResponseCode::InternalServerError);
		responseJson["code"] = -10500;
		responseJson["msg"] = "Server Internal Error";
		std::cout << e.what() << std::endl;
	}
	response.body = responseJson.dump();
	return response;
}

HTTPPacket::HTTPResponsePacket NekoDeliveryAuth::loginAccount(HTTPPacket::HTTPRequestPacket request) noexcept
{
	HTTPPacket::HTTPResponsePacket response;
	auto responseJson = nlohmann::json();
	auto requestParams = webstring::ParseKeyValue(request.body);
	try 
	{
		//std::string sessionId = request.GetCookieValue("sessionId");
		//std::string sessionToken = request.GetCookieValue("sessionToken");
		if (checkPhoneFormat(requestParams["phone"]) == true)
		{
			auto userAuth = userDao->getUserAuthByPhone(std::stoul(requestParams["phone"]));
			if (userAuth != nullptr)
			{
				std::string culculatedHash = webstring::sha1(userAuth->auth_salt + webstring::sha1(requestParams["password"]));
				if (userAuth->auth_hash == culculatedHash)
				{
					unsigned long sessionId = 0;
					std::string sessionToken;
					if (sessionManager->createSession(sessionId, sessionToken))
					{
						Attribute props;
						props["uid"] = userAuth->uid;
						sessionManager->saveAttribute(sessionId, sessionToken, props);
						response.SetResponseCode(HTTPPacket::ResponseCode::OK);
						response.SetCookie("sessionId", std::to_string(sessionId), 30 * 24 * 60 * 60 * 1000l);
						response.SetCookie("sessionToken", sessionToken, 30 * 24 * 60 * 60 * 1000l);
						return response;
					}
					else
					{
						response.SetResponseCode(HTTPPacket::ResponseCode::InternalServerError);
						return response;
					}
				}
			}
		}
		response.SetResponseCode(HTTPPacket::ResponseCode::OK);
		response.SetContentType("application/json; charset=utf8");
		responseJson["code"] = -10011;
		responseJson["msg"] = "用户名或密码错误";
		response.body = responseJson.dump();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		response.SetResponseCode(HTTPPacket::ResponseCode::InternalServerError);
	}
	return response;
}

HTTPPacket::HTTPResponsePacket NekoDeliveryAuth::resetPassword(HTTPPacket::HTTPRequestPacket request) noexcept
{
	HTTPPacket::HTTPResponsePacket response;
	response.SetContentType("application/json; charset=utf8");
	try
	{
		auto requestParams = webstring::ParseKeyValue(request.requestParam);
		unsigned long phone = std::stoul(requestParams["phone"]);
		std::string vcode = requestParams["vcode"];

		std::vector<RecoverCode> records = userDao->getRecoverCode(phone,1);
		time_t currentTime = time(nullptr);
		bool passed = false;
		for (auto& record : records)
		{
			if (currentTime - record.ctime < 5 * 60 * 1000l && vcode == record.vcode)
			{
				passed = true;
				break;
			}
		}

		if (passed)
		{
			auto userAuth = userDao->getUserAuthByPhone(phone);
			if (userAuth == nullptr)
			{
				response.body = "{\"code\": -10005, \"msg\":\"用户不存在\"}";
				return response;
			}
			userAuth->auth_salt = webstring::GenUUID() + webstring::GenTimeStamp();
			userAuth->auth_hash = webstring::sha1(requestParams["password"]);
			userAuth->auth_hash = webstring::sha1(userAuth->auth_salt + userAuth->auth_hash);
			userDao->updateUserAuth(*userAuth);

			response.body = "{\"code\": 0, \"msg\":\"重置密码成功\"}";
			return response;
		}
		else
		{
			response.body = "{\"code\": -10010, \"msg\":\"重置验证码错误\"}";
			return response;
		}
	}
	catch (std::invalid_argument& e)
	{
		response.body = "{\"code\": -10001, \"msg\":\"手机号码格式错误\"}";
		return response;
	}
	catch (const std::exception& e)
	{
		response.body = "{\"code\": -10500, \"msg\":\"服务端错误\"}";
		return response;
	}
}

HTTPPacket::HTTPResponsePacket NekoDeliveryAuth::updateDetail(HTTPPacket::HTTPRequestPacket request) noexcept
{
	HTTPPacket::HTTPResponsePacket response;
	response.SetContentType(HTTPPacket::ContentType::JSON);
	try
	{
		std::string sessionId = request.GetCookieValue("sessionId");
		std::string sessionToken = request.GetCookieValue("sessionToken");
		PtrAttribute props = sessionManager->getAttribute(sessionId, sessionToken);
		if (props == nullptr)
		{
			response.body = "{\"code\": -10012, \"msg\":\"未登录\"}";
			return response;
		}


		auto requestParams = webstring::ParseKeyValue(request.requestParam);
		PtrUserDetail userDetail = userDao->getUserDetailByUid((*props)["props"].get<unsigned int>());
		std::string name = requestParams["name"];
		std::string nick = requestParams["nick"];
		if (name != "")
		{
			userDetail->name = name;
		}
		if (nick != "")
		{
			userDetail->nick = nick;
		}
		userDao->updateUserDetail(*userDetail);
		response.body = "{\"code\": 0, \"msg\":\"更新成功\"}";
		return response;
	}
	catch (const std::exception& e)
	{
		response.body = "{\"code\": -10500, \"msg\":\"服务端错误\"}";
		return response;
	}
	response.SetResponseCode(HTTPPacket::ResponseCode::InternalServerError);
	return response;
}

bool NekoDeliveryAuth::checkPhoneFormat(std::string phone) noexcept
{
	using namespace boost;
	regex fmt("[0-9]{11}");
	return regex_match(phone, fmt);
}

bool NekoDeliveryAuth::checkPasswordFormat(std::string password) noexcept
{
	if (password.size() < 8 || password.size() > 20) {
		return false;
	}

	using namespace boost;
	regex fmt("[0-9a-zA-Z_]+");
	return regex_match(password, fmt);
}
