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
	* ע���û�
	*/
	bool registerAccount(const UserDetail& userDetail, const UserAuth& userAuth) noexcept(false);

	/*
	* ����uid�����û���Ϣ
	*/
	void updateUserDetail(const UserDetail& userDetail);

	/*
	* ����uid��ѯ�û���Ϣ
	*/
	PtrUserDetail getUserDetailByUid(unsigned int uid);

	/*
	* �����ֻ��Ų�ѯ�û���Ϣ
	*/
	PtrUserDetail getUserDetailByPhone(unsigned long phone);

	/*
	* ����uid�����û���֤��Ϣ
	*/
	void updateUserAuth(const UserAuth& userAuth);

	/*
	* ����uid��ȡ�û���֤��Ϣ
	*/
	PtrUserAuth getUserAuthByUid(unsigned int uid);

	/*
	* �����ֻ��Ż�ȡ�û���֤��Ϣ
	*/
	PtrUserAuth getUserAuthByPhone(unsigned long phone);

	/*
	* ��ӿ��Ա��Ϣ
	*/
	void saveCourierInfo(const CouriersInfo& courierInfo);

	/*
	* ����uid��ȡ���Ա��Ϣ
	*/
	PtrCouriersInfo getCourierInfo(unsigned int uid);

	/*
	* ������֤��֤��
	*/
	void saveAccessCode(const AccessCode& accessCode);

	/*
	* �����ֻ��ź�ָ����ʱ���ȡ��֤���¼
	*/
	std::vector<AccessCode> getAccessCode(unsigned long phone, unsigned int max);

	/*
	* ��������������֤��
	*/
	void saveRecoverCode(const RecoverCode& recoverCode);

	/*
	* �����ֻ��Ų�ѯ����������֤��
	*/
	std::vector<RecoverCode> getRecoverCode(unsigned long phone, unsigned int max);
};