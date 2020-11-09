#include "NekoDeliveryUserDaoImpl.h"

void NekoDeliveryUserDaoImpl::registerAccount(const UserDetail& userDetail, const UserAuth& userAuth) noexcept(false)
{
	PtrConnection conn = pool.getConnection();
	conn->setSchema("nekodelivery_user");
	PtrStatement st(conn->createStatement());

	st->execute("BEGIN");
	PtrPreParedStatement ptsm(conn->prepareStatement("INSERT INTO user_detail(phone, nick, name, avatar,register_date,state) VALUES(?,?,?,?,?,?)"));
	ptsm->setUInt(1, userDetail.phone);
	ptsm->setString(2, userDetail.nick);
	ptsm->setString(3, userDetail.name);
	ptsm->setString(4, userDetail.avatar);
	ptsm->setDateTime(5, std::to_string(userDetail.register_date));
	ptsm->setInt(6, userDetail.state);
	ptsm->execute();
	st->execute("SET @lastInsertId = LAST_INSERT_ID()");
	ptsm.reset(conn->prepareStatement("INSERT INTO user_auth(uid, phone, auth_salt, auth_hash, update_date) VALUES(@lastInsertId,?,?,?,?)"));
	ptsm->setUInt(1, userAuth.phone);
	ptsm->setString(2, userAuth.auth_salt);
	ptsm->setString(3, userAuth.auth_hash);
	ptsm->setDateTime(4, std::to_string(userAuth.update_date));
	ptsm->execute();
	st->execute("COMMIT");
	pool.releaseConnection(conn);
}


void NekoDeliveryUserDaoImpl::updateUserDetail(const UserDetail& userDetail)
{

}

std::vector<UserDetail> NekoDeliveryUserDaoImpl::getUserDetailByUid(unsigned int uid)
{
	PtrResultSet result(executeQuery("nekodelivery_user",
									 "SELECT uid, phone, nick, avatar, register_date, state, name FROM user_detail WHERE uid=?",
									 [uid](PtrPreParedStatement ptsm) {ptsm->setUInt(1, uid);})
	);
	std::vector<UserDetail> ret;
	while (result->next())
	{
		UserDetail userDetail = {};
		userDetail.uid = result->getUInt(1);
		userDetail.phone = result->getUInt(2);
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

}


void NekoDeliveryUserDaoImpl::updateUserAuth(const UserAuth& userAUth)
{

}


std::vector<UserAuth> NekoDeliveryUserDaoImpl::getUserAuthByUid(unsigned int uid)
{

}

std::vector<UserAuth> NekoDeliveryUserDaoImpl::getUserAuthByPhone(unsigned int phone)
{

}


void NekoDeliveryUserDaoImpl::saveCourierInfo(const CouriersInfo& courierInfo)
{

}

std::vector<CouriersInfo> NekoDeliveryUserDaoImpl::getCourierInfo(unsigned int uid)
{

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

std::vector<RecoverCode> NekoDeliveryUserDaoImpl::getRecoverCode(unsigned int phone)
{

}
