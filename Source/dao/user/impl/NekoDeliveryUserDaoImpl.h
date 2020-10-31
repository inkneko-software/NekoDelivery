#include "../NekoDeliveryUserDao.h"
#include "../../mysql/MySQLBaseDao.h"
class NekoDeliveryUserDaoImpl : public NekoDeliveryUserDao, private MySQLBaseDao
{
public:
	NekoDeliveryUserDaoImpl()
	{
	
	}

	void registerAccount();
	void saveUserDetail(const UserDetail& userDetail);
	UserDetail getUserDetailByUid(unsigned int uid);
	UserDetail getUserDetailByPhone(unsigned int phone);

	void saveUserAuth(const UserAuth& userAUth);
	UserAuth getUserAuthByUid(unsigned int uid);
	UserAuth getUserAuthByPhone(unsigned int phone);

	void saveCourierInfo(const CouriersInfo& courierInfo);
	CouriersInfo getCourierInfo(unsigned int uid);

	void saveAccessCode(const AccessCode& userDetail);
	AccessCode getAccessCode(unsigned int phone);

	void saveRecoverCode(const RecoverCode& recoverCode);
	RecoverCode getRecoverCode(unsigned int phone);
};