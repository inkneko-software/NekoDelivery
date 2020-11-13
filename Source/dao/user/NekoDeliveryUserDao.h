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
	/// ע���û�
	/// </summary>
	/// <param name="userDetail">�û���userDetail����</param>
	/// <param name="userAuth">�û���userAuth����</param>
	virtual void registerAccount(const UserDetail& userDetail, const UserAuth& userAuth) noexcept(false) = 0;
	/// <summary>
	/// ����userDetail.uid����ָ��userDetail
	/// </summary>
	/// <param name="userDetail">ָ����userDetail</param>
	virtual void updateUserDetail(const UserDetail& userDetail) = 0;
	/// <summary>
	/// ����uid��ȡuserDetail
	/// </summary>
	/// <param name="uid">ָ����uid</param>
	/// <returns>����������userDetail</returns>
	virtual std::vector<UserDetail> getUserDetailByUid(unsigned int uid) = 0;
	/// <summary>
	/// ����phone��ȡuserDetail
	/// </summary>
	/// <param name="phone"></param>
	/// <returns>����������userDetail</returns>
	virtual std::vector<UserDetail> getUserDetailByPhone(unsigned int phone) = 0;
	/// <summary>
	/// ����uid����ָ����userAuth
	/// </summary>
	/// <param name="userAUth">ָ����userAuth</param>
	virtual void updateUserAuth(const UserAuth& userAUth) = 0;
	/// <summary>
	/// ����uid��ѯuserAuth
	/// </summary>
	/// <param name="uid">ָ����uid</param>
	/// <returns>����������userAuth</returns>
	virtual std::vector<UserAuth> getUserAuthByUid(unsigned int uid) = 0;
	/// <summary>
	/// ����phone��ѯuserAuth
	/// </summary>
	/// <param name="phone">ָ����phone</param>
	/// <returns>����������userAuth</returns>
	virtual std::vector<UserAuth> getUserAuthByPhone(unsigned int phone) = 0;
	/// <summary>
	/// ����courierInfo
	/// </summary>
	/// <param name="courierInfo">Ҫ�������Ŀ</param>
	virtual void saveCourierInfo(const CouriersInfo& courierInfo) = 0;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="uid"></param>
	/// <returns></returns>
	virtual std::vector<CouriersInfo> getCourierInfo(unsigned int uid) = 0;
	/// <summary>
	/// ����accessCode
	/// </summary>
	/// <param name="accessCode">Ҫ�������Ŀ</param>
	virtual void saveAccessCode(const AccessCode& accessCode) = 0;
	/// <summary>
	/// �����ֻ��ź��޶�ʱ���ѯaccessCode
	/// </summary>
	/// <param name="phone">ָ�����ֻ���</param>
	/// <param name="max">����ʱ�䵹�����ȡ������</param>
	/// <returns>����������accessCode</returns>
	virtual std::vector<AccessCode> getAccessCode(unsigned int phone, unsigned int max) = 0;
	/// <summary>
	/// ����recoverCode
	/// </summary>
	/// <param name="recoverCode">Ҫ�������֤��</param>
	virtual void saveRecoverCode(const RecoverCode& recoverCode) = 0;
	/// <summary>
	/// ��ѯ��֤��
	/// </summary>
	/// <param name="phone">�ֻ���</param>
	/// <param name="max">����ʱ�䵹�����ȡ������</param>
	/// <returns>����������recoverCode</returns>
	virtual std::vector<RecoverCode> getRecoverCode(unsigned int phone, unsigned int max) = 0;

	virtual ~NekoDeliveryUserDao() {}
};