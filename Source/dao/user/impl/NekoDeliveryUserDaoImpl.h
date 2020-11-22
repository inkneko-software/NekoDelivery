#include "../NekoDeliveryUserDao.h"
#include "../../mysql/MySQLBaseDao.h"
class NekoDeliveryUserDaoImpl : public NekoDeliveryUserDao, private MySQLBaseDao
{
public:
	NekoDeliveryUserDaoImpl(std::string host, unsigned short port, std::string user, std::string password, size_t maintainSize)
		: MySQLBaseDao(host, port, user, password, maintainSize)
	{
		
	}

	/*
	* 注册用户
	*/
	bool registerAccount(const UserDetail& userDetail, const UserAuth& userAuth) noexcept(false);

	/*
	* 根据uid更新用户信息
	*/
	void updateUserDetail(const UserDetail& userDetail);

	/*
	* 根据uid查询用户信息
	*/
	PtrUserDetail getUserDetailByUid(unsigned int uid);

	/*
	* 根据手机号查询用户信息
	*/
	PtrUserDetail getUserDetailByPhone(unsigned long phone);

	/*
	* 根据uid更新用户认证信息
	*/
	void updateUserAuth(const UserAuth& userAuth);

	/*
	* 根据uid获取用户认证信息
	*/
	PtrUserAuth getUserAuthByUid(unsigned int uid);

	/*
	* 根据手机号获取用户认证信息
	*/
	PtrUserAuth getUserAuthByPhone(unsigned long phone);

	/*
	* 添加快递员信息
	*/
	void saveCourierInfo(const CouriersInfo& courierInfo);

	/*
	* 根据uid获取快递员信息
	*/
	PtrCouriersInfo getCourierInfo(unsigned int uid);

	/*
	* 保存认证验证码
	*/
	void saveAccessCode(const AccessCode& accessCode);

	/*
	* 根据手机号和指定的时间获取认证码记录
	*/
	std::vector<AccessCode> getAccessCode(unsigned long phone, unsigned int max);

	/*
	* 保存重置密码验证码
	*/
	void saveRecoverCode(const RecoverCode& recoverCode);

	/*
	* 根据手机号查询重置密码验证码
	*/
	std::vector<RecoverCode> getRecoverCode(unsigned long phone, unsigned int max);
};