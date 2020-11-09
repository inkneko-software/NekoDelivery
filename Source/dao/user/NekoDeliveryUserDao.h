#pragma once
#include <string>
#include <vector>

#include "table/UserDetail.h"
#include "table/UserAuth.h"
#include "table/CouriersInfo.h"
#include "table/AccessCode.h"
#include "table/RecoverCode.h"

class NekoDeliveryUserDao
{
public:
	NekoDeliveryUserDao() = default;

	virtual void registerAccount(const UserDetail& userDetail, const UserAuth& userAuth) noexcept(false) = 0;
	virtual void updateUserDetail(const UserDetail& userDetail) = 0;
	virtual std::vector<UserDetail> getUserDetailByUid(unsigned int uid) = 0;
	virtual std::vector<UserDetail> getUserDetailByPhone(unsigned int phone) = 0;

	virtual void updateUserAuth(const UserAuth& userAUth) = 0;
	virtual std::vector<UserAuth> getUserAuthByUid(unsigned int uid) = 0;
	virtual std::vector<UserAuth> getUserAuthByPhone(unsigned int phone) = 0;

	virtual void saveCourierInfo(const CouriersInfo& courierInfo) = 0;
	virtual std::vector<CouriersInfo> getCourierInfo(unsigned int uid) = 0;

	virtual void saveAccessCode(const AccessCode& accessCode) = 0;
	virtual std::vector<AccessCode> getAccessCode(unsigned int phone, unsigned int ctime) = 0;

	virtual void saveRecoverCode(const RecoverCode& recoverCode) = 0;
	virtual std::vector<RecoverCode> getRecoverCode(unsigned int phone) = 0;

	virtual ~NekoDeliveryUserDao() {}
};