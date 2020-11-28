#include "NekoDeliverySession.h"
#include <tinyHttpd/webstring.h>
NekoDeliverySession::NekoDeliverySession()
{
	sessionDao.reset(new NekoDeliverySessionDaoImpl("127.0.0.1", 3306, "dev_leaf", "leaf", 10));
}

bool NekoDeliverySession::createSession(unsigned long& outSessionId, std::string& outSessionToken, unsigned long expiredTime)
{
	SessionToken sessionToken;
	sessionToken.session_id = 0;
	sessionToken.create_time = time(nullptr);
	sessionToken.expire_time = sessionToken.create_time + expiredTime;
	sessionToken.token = webstring::sha1(webstring::GenUUID() + std::to_string(sessionToken.create_time));
	if (sessionDao->saveSessionToken(sessionToken) == true)
	{
		outSessionId = sessionToken.session_id;
		outSessionToken = sessionToken.token;
		return true;
	}
	return false;
}

PtrAttribute NekoDeliverySession::getAttribute(unsigned long sessionId, std::string sessionToken)
{
	PtrAttribute ret(nullptr);
	PtrSessionToken session(sessionDao->getSessionToken(sessionId, sessionToken));
	if (session != nullptr)
	{
		if (time(nullptr) < session->expire_time)
		{
			PtrSessionProperties sessionProperties(sessionDao->getSessionProperties(sessionId));
			ret.reset(new nlohmann::json(nlohmann::json::parse(sessionProperties->serialized_text)));
		}
	}
	return ret;
}

PtrAttribute NekoDeliverySession::getAttribute(std::string sessionId, std::string sessionToken) noexcept(false)
{
	if (sessionId == "" || sessionToken != "")
	{
		return nullptr;
	}
	try
	{
		unsigned long sessionIdInt = std::stoul(sessionId);
		return getAttribute(sessionIdInt, sessionToken);
	}
	catch (std::invalid_argument& e) {}
	return nullptr;
}

bool NekoDeliverySession::saveAttribute(unsigned long sessionId, std::string sessionToken, Attribute& attribute)
{
	PtrSessionToken session(sessionDao->getSessionToken(sessionId, sessionToken));
	if (session != nullptr)
	{
		if (time(nullptr) > session->expire_time)
		{
			throw SessionExpiredException("会话已过期");
		}
		sessionDao->updateSessionProperties({sessionId, attribute.dump()});
		return true;
	}
	return false;
}
