#pragma once
#include <string>

#include "table/UserDetail.h"
#include "table/UserAuth.h"
#include "table/CouriersInfo.h"
#include "table/AccessCode.h"
#include "table/RecoverCode.h"

class NekoDeliveryUserDao
{
public:
	NekoDeliveryUserDao() = default;

	virtual void registerAccount() = 0;
	virtual void saveUserDetail(const UserDetail& userDetail) = 0;
	virtual UserDetail getUserDetailByUid(unsigned int uid) = 0;
	virtual UserDetail getUserDetailByPhone(unsigned int phone) = 0;

	virtual void saveUserAuth(const UserAuth& userAUth) = 0;
	virtual UserAuth getUserAuthByUid(unsigned int uid) = 0;
	virtual UserAuth getUserAuthByPhone(unsigned int phone) = 0;

	virtual void saveCourierInfo(const CouriersInfo& courierInfo) = 0;
	virtual CouriersInfo getCourierInfo(unsigned int uid) = 0;

	virtual void saveAccessCode(const AccessCode& userDetail) = 0;
	virtual AccessCode getAccessCode(unsigned int phone) = 0;

	virtual void saveRecoverCode(const RecoverCode& recoverCode) = 0;
	virtual RecoverCode getRecoverCode(unsigned int phone) = 0;
};