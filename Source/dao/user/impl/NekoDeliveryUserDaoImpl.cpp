#include "NekoDeliveryUserDaoImpl.h"
void NekoDeliveryUserDaoImpl::registerAccount()
{
}

void NekoDeliveryUserDaoImpl::saveUserDetail(const UserDetail& userDetail)
{

}

UserDetail NekoDeliveryUserDaoImpl::getUserDetailByUid(unsigned int uid)
{
	UserDetail detail;
	detail.name = "leaf";
	detail.uid = uid;
	detail.phone = 110;
	return detail;
}

UserDetail NekoDeliveryUserDaoImpl::getUserDetailByPhone(unsigned int phone)
{
	return UserDetail();
}

void NekoDeliveryUserDaoImpl::saveUserAuth(const UserAuth& userAUth)
{
}

UserAuth NekoDeliveryUserDaoImpl::getUserAuthByUid(unsigned int uid)
{
	return UserAuth();
}

UserAuth NekoDeliveryUserDaoImpl::getUserAuthByPhone(unsigned int phone)
{
	return UserAuth();
}

void NekoDeliveryUserDaoImpl::saveCourierInfo(const CouriersInfo& courierInfo)
{
}

CouriersInfo NekoDeliveryUserDaoImpl::getCourierInfo(unsigned int uid)
{
	return CouriersInfo();
}

void NekoDeliveryUserDaoImpl::saveAccessCode(const AccessCode& userDetail)
{
}

AccessCode NekoDeliveryUserDaoImpl::getAccessCode(unsigned int phone)
{
	return AccessCode();
}

void NekoDeliveryUserDaoImpl::saveRecoverCode(const RecoverCode& recoverCode)
{
}

RecoverCode NekoDeliveryUserDaoImpl::getRecoverCode(unsigned int phone)
{
	return RecoverCode();
}
