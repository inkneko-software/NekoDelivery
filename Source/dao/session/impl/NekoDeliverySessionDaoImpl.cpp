#include "NekoDeliverySessionDaoImpl.h"

#include <tinyHttpd/webstring.h>

bool NekoDeliverySessionDaoImpl::saveSessionToken(SessionToken& sessionToken)
{
	PtrConnection conn(pool.getConnection());
	conn->setSchema(dbname);

	PtrStatement statement(conn->createStatement());
	statement->execute("BEGIN");
	PtrPreparedStatement ptsm(conn->prepareStatement("INSERT INTO session_token(token, create_time, expire_time) VALUES(?,?,?)"));
	ptsm->setString(1, sessionToken.token);
	ptsm->setUInt(2, sessionToken.create_time);
	ptsm->setUInt(3, sessionToken.expire_time);
	int affectedNum = ptsm->executeUpdate();
	if (affectedNum == 0) {
		statement->execute("ROLLBACK");
		return false;
	}

	statement->execute("SET @lastInsertId = LAST_INSERT_ID()");
	affectedNum = statement->executeUpdate("INSERT INTO session_properties VALUES(@lastInsertId,\'\')");
	if (affectedNum == 0) {
		statement->execute("ROLLBACK");
		return false;
	}
	statement->execute("COMMIT");

	PtrResultSet result(statement->executeQuery("SELECT @lastInsertId"));
	result->next();
	sessionToken.session_id = result->getUInt64(1);
	return true;
}

PtrSessionToken NekoDeliverySessionDaoImpl::getSessionToken(unsigned long sessionId, std::string sessionToken)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT session_id, token, create_time, expire_time FROM session_token WHERE session_id=? AND token=?",
		[sessionId, sessionToken](PtrPreparedStatement ptsm) {
			ptsm->setUInt64(1, sessionId);
			ptsm->setString(2, sessionToken);
		}
	));
	if (result->next())
	{
		PtrSessionToken sessionToken(new SessionToken());
		sessionToken->session_id = result->getUInt64(1);
		sessionToken->token = result->getString(2);
		sessionToken->create_time = result->getUInt(3);
		sessionToken->expire_time = result->getUInt(4);
		return sessionToken;
	}
	return nullptr;
}

bool NekoDeliverySessionDaoImpl::updateSessionToken(const SessionToken& sessionToken)
{
	int affectedNum = executeUpdate(
		dbname,
		"UPDATE session_token SET create_time=?, expire_time=? WHERE session_id=? AND token=?",
		[sessionToken](PtrPreparedStatement ptsm) {
			ptsm->setUInt(1, sessionToken.create_time);
			ptsm->setUInt(2, sessionToken.expire_time);
			ptsm->setUInt64(3, sessionToken.session_id);
			ptsm->setString(4, sessionToken.token);
		}
	);
	return affectedNum != 0;
}

bool NekoDeliverySessionDaoImpl::saveSessionProperties(const SessionProperties& sessionProperites)
{
	int affectedNum = executeUpdate(
		dbname,
		"INSERT INTO session_properties(session_id,serialized_text) VALUES(?,?)",
		[sessionProperites](PtrPreparedStatement ptsm) {
			ptsm->setUInt64(1, sessionProperites.session_id);
			ptsm->setString(2, sessionProperites.serialized_text);
		}
	);
	return affectedNum != 0;
}

PtrSessionProperties NekoDeliverySessionDaoImpl::getSessionProperties(unsigned long sessionId)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT serialized_text FROM session_properties WHERE session_id=?",
		[sessionId](PtrPreparedStatement ptsm) {
			ptsm->setUInt64(1, sessionId);
		}
	));
	if (result->next())
	{
		PtrSessionProperties props(new SessionProperties);
		props->serialized_text = result->getString(1);
		props->session_id = sessionId;
		return props;
	}
	return nullptr;
}

bool NekoDeliverySessionDaoImpl::updateSessionProperties(const SessionProperties& sessionProperties)
{
	int affectedNum = executeUpdate(
		dbname,
		"UPDATE session_properties SET serialized_text=? WHERE session_id=?",
		[sessionProperties](PtrPreparedStatement ptsm) {
			ptsm->setString(1, sessionProperties.serialized_text);
			ptsm->setUInt64(2, sessionProperties.session_id);
		}
	);
	return affectedNum != 0;
}
