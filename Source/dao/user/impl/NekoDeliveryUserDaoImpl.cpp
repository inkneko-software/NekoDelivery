#include "NekoDeliveryUserDaoImpl.h"

bool NekoDeliveryUserDaoImpl::registerAccount(const UserDetail& userDetail, const UserAuth& userAuth) noexcept(false)
{
	PtrConnection conn = pool.getConnection();
	conn->setSchema(dbname);
	PtrStatement st(conn->createStatement());

	st->execute("BEGIN");
	PtrPreparedStatement ptsm(conn->prepareStatement("INSERT INTO user_detail(phone, nick, name, avatar,register_date,state) VALUES(?,?,?,?,?,?)"));
	ptsm->setUInt64(1, userDetail.phone);
	ptsm->setString(2, userDetail.nick);
	ptsm->setString(3, userDetail.name);
	ptsm->setString(4, userDetail.avatar);
	ptsm->setUInt(5, userDetail.register_date);
	ptsm->setInt(6, userDetail.state);
	int affectedNum = ptsm->executeUpdate();
	if (affectedNum == 0) {
		st->execute("ROLLBACK");
		return false;
	}
	st->execute("SET @lastInsertId = LAST_INSERT_ID()");
	ptsm.reset(conn->prepareStatement("INSERT INTO user_auth(uid, phone, auth_salt, auth_hash, update_date) VALUES(@lastInsertId,?,?,?,?)"));
	ptsm->setUInt64(1, userAuth.phone);
	ptsm->setString(2, userAuth.auth_salt);
	ptsm->setString(3, userAuth.auth_hash);
	ptsm->setUInt(4, userAuth.update_date);
	ptsm->execute();
	st->execute("COMMIT");
	pool.releaseConnection(conn);

	return true;
}


void NekoDeliveryUserDaoImpl::updateUserDetail(const UserDetail& userDetail)
{
	executeUpdate(
		dbname,
		"UPDATE user_detail SET phone=?, nick=?, name=?, avatar=?, register_date=?, state=? WHERE uid=?",
		[userDetail](PtrPreparedStatement ptsm) {
			ptsm->setUInt64(1, userDetail.phone);
			ptsm->setString(2, userDetail.nick);
			ptsm->setString(3, userDetail.name);
			ptsm->setString(4, userDetail.avatar);
			ptsm->setUInt(5, userDetail.register_date);
			ptsm->setInt(6, userDetail.state);
			ptsm->setUInt(7, userDetail.uid);
		});
}

PtrUserDetail NekoDeliveryUserDaoImpl::getUserDetailByUid(unsigned int uid)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT uid, phone, nick, avatar, register_date, state, name FROM user_detail WHERE uid=?",
		[uid](PtrPreparedStatement ptsm) {ptsm->setUInt(1, uid);})
	);
	if (result->next())
	{
		PtrUserDetail userDetail(new UserDetail);
		userDetail->uid = result->getUInt(1);
		userDetail->phone = result->getUInt64(2);
		userDetail->nick = result->getString(3);
		userDetail->avatar = result->getString(4);
		userDetail->register_date = result->getUInt(5);
		userDetail->state = result->getInt(6);
		userDetail->name = result->getString(7);
		return userDetail;
	}
	return nullptr;
}


PtrUserDetail NekoDeliveryUserDaoImpl::getUserDetailByPhone(unsigned long phone)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT uid, phone, nick, avatar, register_date, state, name FROM user_detail WHERE phone=?",
		[phone](PtrPreparedStatement ptsm) {ptsm->setUInt64(1, phone); })
	);
	if (result->next())
	{
		PtrUserDetail userDetail(new UserDetail);
		userDetail->uid = result->getUInt(1);
		userDetail->phone = result->getUInt64(2);
		userDetail->nick = result->getString(3);
		userDetail->avatar = result->getString(4);
		userDetail->register_date = result->getUInt(5);
		userDetail->state = result->getInt(6);
		userDetail->name = result->getString(7);
		return userDetail;
	}
	return nullptr;
}


void NekoDeliveryUserDaoImpl::updateUserAuth(const UserAuth& userAuth)
{
	executeUpdate(
		"nekodelivery_user",
		"UPDATE user_auth SET phone=?, auth_salt=?, auth_hash=?, update_date=? WHERE uid=?",
		[userAuth](PtrPreparedStatement ptsm) {
			ptsm->setUInt64(1, userAuth.phone);
			ptsm->setString(2, userAuth.auth_salt);
			ptsm->setString(3, userAuth.auth_hash);
			ptsm->setUInt(4, userAuth.update_date);
			ptsm->setUInt(5, userAuth.uid);
		});
}


PtrUserAuth NekoDeliveryUserDaoImpl::getUserAuthByUid(unsigned int uid)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT uid, phone, auth_salt, auth_hash, update_date FROM user_auth WHERE uid=?",
		[uid](PtrPreparedStatement ptsm) {ptsm->setUInt(1, uid); }
	));
	if (result->next())
	{
		PtrUserAuth userAuth(new UserAuth);
		userAuth->uid = result->getUInt(1);
		userAuth->phone = result->getUInt64(2);
		userAuth->auth_salt = result->getString(3);
		userAuth->auth_hash = result->getString(4);
		userAuth->update_date = result->getUInt(5);
		return userAuth;
	}
	return nullptr;
}

PtrUserAuth NekoDeliveryUserDaoImpl::getUserAuthByPhone(unsigned long phone)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT uid, phone, auth_salt, auth_hash, update_date FROM user_auth WHERE phone=?",
		[phone](PtrPreparedStatement ptsm) {ptsm->setUInt64(1, phone); }
	));
	if (result->next())
	{
		PtrUserAuth userAuth(new UserAuth);
		userAuth->uid = result->getUInt(1);
		userAuth->phone = result->getUInt64(2);
		userAuth->auth_salt = result->getString(3);
		userAuth->auth_hash = result->getString(4);
		userAuth->update_date = result->getUInt(5);
		return userAuth;
	}
	return nullptr;
}


void NekoDeliveryUserDaoImpl::saveCourierInfo(const CouriersInfo& courierInfo)
{
	executeUpdate(
		dbname,
		"INSERT INTO courier_info(uid, passport_front, passport_detail, operator_id, accept_date) values(?,?,?,?,?)",
		[courierInfo](PtrPreparedStatement ptsm) {
			ptsm->setUInt(1, courierInfo.uid);
			ptsm->setString(2, courierInfo.passport_front);
			ptsm->setString(3, courierInfo.passport_detail);
			ptsm->setUInt(4, courierInfo.operator_id);
			ptsm->setUInt(5, courierInfo.accept_date);
		}
	);
}

PtrCouriersInfo NekoDeliveryUserDaoImpl::getCourierInfo(unsigned int uid)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT uid, passport_front, passport_detail, operator_id, accept_date FROM user_courier_info WHERE uid=?",
		[uid](PtrPreparedStatement ptsm) {ptsm->setUInt(1, uid); }
	));
	if (result->next())
	{
		PtrCouriersInfo couriersInfo(new CouriersInfo);
		couriersInfo->uid = result->getUInt(1);
		couriersInfo->passport_front = result->getString(2);
		couriersInfo->passport_detail = result->getString(3);
		couriersInfo->operator_id = result->getUInt(4);
		couriersInfo->accept_date = result->getUInt(5);
		return couriersInfo;
	}
	return nullptr;
}

void NekoDeliveryUserDaoImpl::saveAccessCode(const AccessCode& accessCode)
{
	executeUpdate(
		dbname, 
		"INSERT INTO access_code VALUES(?,?,?)",
		[accessCode](PtrPreparedStatement ptsm) {
			ptsm->setUInt64(1, accessCode.phone);
			ptsm->setString(2, accessCode.vcode);
			ptsm->setUInt(3, accessCode.ctime);
		}
	);
}


std::vector<AccessCode> NekoDeliveryUserDaoImpl::getAccessCode(unsigned long phone, unsigned int max)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT phone, vcode, ctime FROM access_code WHERE phone=? ORDER BY ctime ASC LIMIT ?",
		[phone, max](PtrPreparedStatement ptsm) {
			ptsm->setUInt64(1, phone);
			ptsm->setInt(2, max);
		}
	));

	std::vector<AccessCode> ret;
	while (result->next())
	{
		AccessCode ac;
		ac.phone = result->getUInt64(1);
		ac.vcode = result->getString(2);
		ac.ctime = result->getUInt(3);
		ret.push_back(ac);
	}
	return ret;
}

void NekoDeliveryUserDaoImpl::saveRecoverCode(const RecoverCode& recoverCode)
{
	executeUpdate(
		dbname,
		"INSERT INTO recover_code VALUES(?,?,?)",
		[recoverCode](PtrPreparedStatement ptsm) {
			ptsm->setUInt64(1, recoverCode.phone);
			ptsm->setString(2, recoverCode.vcode);
			ptsm->setUInt(3, recoverCode.ctime);
		}
	);
}

std::vector<RecoverCode> NekoDeliveryUserDaoImpl::getRecoverCode(unsigned long phone, unsigned int max)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT phone, vcode, ctime FROM recover_code WHERE phone=? ORDER BY ctime ASC LIMIT ?",
		[phone, max](PtrPreparedStatement ptsm) {
			ptsm->setUInt64(1, phone);
			ptsm->setInt(2, max);
		}
	));

	std::vector<RecoverCode> ret;
	while (result->next())
	{
		RecoverCode rc;
		rc.phone = result->getUInt64(1);
		rc.vcode = result->getString(2);
		rc.ctime = result->getUInt(3);
		ret.push_back(rc);
	}
	return ret;
}
