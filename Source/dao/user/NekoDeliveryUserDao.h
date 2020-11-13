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
protected:
	std::string dbname = "nekodelivery_user";
public:
	NekoDeliveryUserDao() = default;

	/// <summary>
	/// 注册用户
	/// </summary>
	/// <param name="userDetail">用户的userDetail数据</param>
	/// <param name="userAuth">用户的userAuth数据</param>
	virtual void registerAccount(const UserDetail& userDetail, const UserAuth& userAuth) noexcept(false) = 0;
	/// <summary>
	/// 根据userDetail.uid更新指定userDetail
	/// </summary>
	/// <param name="userDetail">指定的userDetail</param>
	virtual void updateUserDetail(const UserDetail& userDetail) = 0;
	/// <summary>
	/// 根据uid获取userDetail
	/// </summary>
	/// <param name="uid">指定的uid</param>
	/// <returns>满足条件的userDetail</returns>
	virtual std::vector<UserDetail> getUserDetailByUid(unsigned int uid) = 0;
	/// <summary>
	/// 根据phone获取userDetail
	/// </summary>
	/// <param name="phone"></param>
	/// <returns>满足条件的userDetail</returns>
	virtual std::vector<UserDetail> getUserDetailByPhone(unsigned int phone) = 0;
	/// <summary>
	/// 根据uid更新指定的userAuth
	/// </summary>
	/// <param name="userAUth">指定的userAuth</param>
	virtual void updateUserAuth(const UserAuth& userAUth) = 0;
	/// <summary>
	/// 根据uid查询userAuth
	/// </summary>
	/// <param name="uid">指定的uid</param>
	/// <returns>满足条件的userAuth</returns>
	virtual std::vector<UserAuth> getUserAuthByUid(unsigned int uid) = 0;
	/// <summary>
	/// 根据phone查询userAuth
	/// </summary>
	/// <param name="phone">指定的phone</param>
	/// <returns>满足条件的userAuth</returns>
	virtual std::vector<UserAuth> getUserAuthByPhone(unsigned int phone) = 0;
	/// <summary>
	/// 保存courierInfo
	/// </summary>
	/// <param name="courierInfo">要保存的条目</param>
	virtual void saveCourierInfo(const CouriersInfo& courierInfo) = 0;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="uid"></param>
	/// <returns></returns>
	virtual std::vector<CouriersInfo> getCourierInfo(unsigned int uid) = 0;
	/// <summary>
	/// 保存accessCode
	/// </summary>
	/// <param name="accessCode">要保存的条目</param>
	virtual void saveAccessCode(const AccessCode& accessCode) = 0;
	/// <summary>
	/// 根据手机号和限定时间查询accessCode
	/// </summary>
	/// <param name="phone">指定的手机号</param>
	/// <param name="max">根据时间倒叙。最多取的数量</param>
	/// <returns>满足条件的accessCode</returns>
	virtual std::vector<AccessCode> getAccessCode(unsigned int phone, unsigned int max) = 0;
	/// <summary>
	/// 保存recoverCode
	/// </summary>
	/// <param name="recoverCode">要保存的验证码</param>
	virtual void saveRecoverCode(const RecoverCode& recoverCode) = 0;
	/// <summary>
	/// 查询验证码
	/// </summary>
	/// <param name="phone">手机号</param>
	/// <param name="max">根据时间倒叙。最多取的数量</param>
	/// <returns>满足条件的recoverCode</returns>
	virtual std::vector<RecoverCode> getRecoverCode(unsigned int phone, unsigned int max) = 0;

	virtual ~NekoDeliveryUserDao() {}
};