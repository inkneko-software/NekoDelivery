#include "NekoDeliveryUserDaoImpl.h"

void NekoDeliveryUserDaoImpl::registerAccount(const UserDetail& userDetail, const UserAuth& userAuth) noexcept(false)
{
	PtrConnection conn = pool.getConnection();
	conn->setSchema(dbname);
	PtrStatement st(conn->createStatement());

	st->execute("BEGIN");
	PtrPreParedStatement ptsm(conn->prepareStatement("INSERT INTO user_detail(phone, nick, name, avatar,register_date,state) VALUES(?,?,?,?,?,?)"));
	ptsm->setUInt64(1, userDetail.phone);
	ptsm->setString(2, userDetail.nick);
	ptsm->setString(3, userDetail.name);
	ptsm->setString(4, userDetail.avatar);
	ptsm->setUInt(5, userDetail.register_date);
	ptsm->setInt(6, userDetail.state);
	ptsm->execute();
	st->execute("SET @lastInsertId = LAST_INSERT_ID()");
	ptsm.reset(conn->prepareStatement("INSERT INTO user_auth(uid, phone, auth_salt, auth_hash, update_date) VALUES(@lastInsertId,?,?,?,?)"));
	ptsm->setUInt(1, userAuth.phone);
	ptsm->setString(2, userAuth.auth_salt);
	ptsm->setString(3, userAuth.auth_hash);
	ptsm->setUInt(4, userAuth.update_date);
	ptsm->execute();
	st->execute("COMMIT");
	pool.releaseConnection(conn);
}


void NekoDeliveryUserDaoImpl::updateUserDetail(const UserDetail& userDetail)
{
	executeUpdate(
		dbname,
		"UPDATE user_detail SET phone=?, nick=?, name=?, avatar=?, register_date=?, state=? WHERE uid=?",
		[userDetail](PtrPreParedStatement ptsm) {
			ptsm->setUInt64(1, userDetail.phone);
			ptsm->setString(2, userDetail.nick);
			ptsm->setString(3, userDetail.name);
			ptsm->setString(4, userDetail.avatar);
			ptsm->setUInt(5, userDetail.register_date);
			ptsm->setInt(6, userDetail.state);
			ptsm->setUInt(7, userDetail.uid);
		});
}

std::vector<UserDetail> NekoDeliveryUserDaoImpl::getUserDetailByUid(unsigned int uid)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT uid, phone, nick, avatar, register_date, state, name FROM user_detail WHERE uid=?",
		[uid](PtrPreParedStatement ptsm) {ptsm->setUInt(1, uid);})
	);
	std::vector<UserDetail> ret;
	while (result->next())
	{
		UserDetail userDetail = {};
		userDetail.uid = result->getUInt(1);
		userDetail.phone = result->getUInt64(2);
		userDetail.nick = result->getString(3);
		userDetail.avatar = result->getString(4);
		userDetail.register_date = result->getUInt(5);
		userDetail.state = result->getInt(6);
		userDetail.name = result->getString(7);
		ret.push_back(userDetail);
	}
	return ret;
}


std::vector<UserDetail> NekoDeliveryUserDaoImpl::getUserDetailByPhone(unsigned int phone)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT uid, phone, nick, avatar, register_date, state, name FROM user_detail WHERE phone=?",
		[phone](PtrPreParedStatement ptsm) {ptsm->setUInt64(1, phone); })
	);
	std::vector<UserDetail> ret;
	while (result->next())
	{
		UserDetail userDetail = {};
		userDetail.uid = result->getUInt(1);
		userDetail.phone = result->getUInt64(2);
		userDetail.nick = result->getString(3);
		userDetail.avatar = result->getString(4);
		userDetail.register_date = result->getUInt(5);
		userDetail.state = result->getInt(6);
		userDetail.name = result->getString(7);
		ret.push_back(userDetail);
	}
	return ret;
}


void NekoDeliveryUserDaoImpl::updateUserAuth(const UserAuth& userAuth)
{
	executeUpdate(
		"nekodelivery_user",
		"UPDATE user_auth SET phone=?, auth_salt=?, auth_hash=?, update_date=? WHERE uid=?",
		[userAuth](PtrPreParedStatement ptsm) {
			ptsm->setUInt64(1, userAuth.phone);
			ptsm->setString(2, userAuth.auth_salt);
			ptsm->setString(3, userAuth.auth_hash);
			ptsm->setUInt(4, userAuth.update_date);
			ptsm->setUInt(5, userAuth.uid);
		});
}


std::vector<UserAuth> NekoDeliveryUserDaoImpl::getUserAuthByUid(unsigned int uid)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT uid, phone, auth_salt, auth_hash, update_date FROM user_auth WHERE uid=?",
		[uid](PtrPreParedStatement ptsm) {ptsm->setUInt(1, uid); }
	));
	std::vector<UserAuth> resultArray;
	while (result->next())
	{
		UserAuth userAuth;
		userAuth.uid = result->getUInt(1);
		userAuth.phone = result->getUInt64(2);
		userAuth.auth_salt = result->getString(3);
		userAuth.auth_hash = result->getString(4);
		userAuth.update_date = result->getUInt(5);
		resultArray.push_back(userAuth);
	}
	return resultArray;
}

std::vector<UserAuth> NekoDeliveryUserDaoImpl::getUserAuthByPhone(unsigned int phone)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT uid, phone, auth_salt, auth_hash, update_date FROM user_auth WHERE phone=?",
		[phone](PtrPreParedStatement ptsm) {ptsm->setUInt(1, phone); }
	));
	std::vector<UserAuth> resultArray;
	while (result->next())
	{
		UserAuth userAuth;
		userAuth.uid = result->getUInt(1);
		userAuth.phone = result->getUInt64(2);
		userAuth.auth_salt = result->getString(3);
		userAuth.auth_hash = result->getString(4);
		userAuth.update_date = result->getUInt(5);
		resultArray.push_back(userAuth);
	}
	return resultArray;
}


void NekoDeliveryUserDaoImpl::saveCourierInfo(const CouriersInfo& courierInfo)
{
	executeUpdate(
		dbname,
		"INSERT INTO courier_info(uid, passport_front, passport_detail, operator_id, accept_date) values(?,?,?,?,?)",
		[courierInfo](PtrPreParedStatement ptsm) {
			ptsm->setUInt(1, courierInfo.uid);
			ptsm->setString(2, courierInfo.passport_front);
			ptsm->setString(3, courierInfo.passport_detail);
			ptsm->setUInt(4, courierInfo.operator_id);
			ptsm->setUInt(5, courierInfo.accept_date);
		}
	);
}

std::vector<CouriersInfo> NekoDeliveryUserDaoImpl::getCourierInfo(unsigned int uid)
{
	PtrResultSet result(executeQuery(
		dbname,
		"SELECT uid, passport_front, passport_detail, operator_id, accept_date FROM user_courier_info WHERE uid=?",
		[uid](PtrPreParedStatement ptsm) {ptsm->setUInt(1, uid); }
	));
	std::vector<CouriersInfo> resultArray;
	while (result->next())
	{
		CouriersInfo couriersInfo;
		couriersInfo.uid = result->getUInt(1);
		couriersInfo.passport_front = result->getString(2);
		couriersInfo.passport_detail = result->getString(3);
		couriersInfo.operator_id = result->getUInt(4);
		couriersInfo.accept_date = result->getUInt(5);
		resultArray.push_back(couriersInfo);
	}
	return resultArray;
}

void NekoDeliveryUserDaoImpl::saveAccessCode(const AccessCode& accessCode)
{

}


std::vector<AccessCode> NekoDeliveryUserDaoImpl::getAccessCode(unsigned int phone, unsigned int ctime)
{

}

void NekoDeliveryUserDaoImpl::saveRecoverCode(const RecoverCode& recoverCode)
{

}

std::vector<RecoverCode> NekoDeliveryUserDaoImpl::getRecoverCode(unsigned int phone, unsigned int ctime)
{

}
