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
	void registerAccount(const UserDetail& userDetail, const UserAuth& userAuth) noexcept(false);

	/*
	* ����uid�����û���Ϣ
	*/
	void updateUserDetail(const UserDetail& userDetail);

	/*
	* ����uid��ѯ�û���Ϣ
	*/
	std::vector<UserDetail> getUserDetailByUid(unsigned int uid);

	/*
	* �����ֻ��Ų�ѯ�û���Ϣ
	*/
	std::vector<UserDetail> getUserDetailByPhone(unsigned int phone);

	/*
	* ����uid�����û���֤��Ϣ
	*/
	void updateUserAuth(const UserAuth& userAUth);

	/*
	* ����uid��ȡ�û���֤��Ϣ
	*/
	std::vector<UserAuth> getUserAuthByUid(unsigned int uid);

	/*
	* �����ֻ��Ż�ȡ�û���֤��Ϣ
	*/
	std::vector<UserAuth> getUserAuthByPhone(unsigned int phone);

	/*
	* ��ӿ��Ա��Ϣ
	*/
	void saveCourierInfo(const CouriersInfo& courierInfo);

	/*
	* ����uid��ȡ���Ա��Ϣ
	*/
	std::vector<CouriersInfo> getCourierInfo(unsigned int uid);

	/*
	* ������֤��֤��
	*/
	void saveAccessCode(const AccessCode& accessCode);

	/*
	* �����ֻ��ź�ָ����ʱ���ȡ��֤���¼
	*/
	std::vector<AccessCode> getAccessCode(unsigned int phone, unsigned int ctime);

	/*
	* ��������������֤��
	*/
	void saveRecoverCode(const RecoverCode& recoverCode);

	/*
	* �����ֻ��Ų�ѯ����������֤��
	*/
	std::vector<RecoverCode> getRecoverCode(unsigned int phone);
};