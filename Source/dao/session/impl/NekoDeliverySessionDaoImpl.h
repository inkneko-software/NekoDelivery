#include "../NekoDeliverySessionDao.h"
#include "../../mysql/MySQLBaseDao.h"

class NekoDeliverySessionDaoImpl : public NekoDeliverySessionDao, private MySQLBaseDao
{
protected:
	std::string dbname = "nekodelivery_session";
public:
	NekoDeliverySessionDaoImpl(std::string host, unsigned short port, std::string user, std::string password, size_t maintainSize)
		: MySQLBaseDao(host, port, user, password, maintainSize)
	{

	}

	bool saveSessionToken(SessionToken& sessionToken);
	PtrSessionToken getSessionToken(unsigned long sessionId, std::string sessionToken);
	bool updateSessionToken(const SessionToken& sessionToken);
	bool saveSessionProperties(const SessionProperties& sessionProperites);
	PtrSessionProperties getSessionProperties(unsigned long sessionId);
	bool updateSessionProperties(const SessionProperties& sessionProperties);
};