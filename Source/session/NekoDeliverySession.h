#include "../dao/session/NekoDeliverySessionDao.h"
#include "../dao/session/impl/NekoDeliverySessionDaoImpl.h"

#include "SessionException.hpp"
#include <nlohmann/json.hpp>

using Attribute = nlohmann::json;
using PtrAttribute = std::unique_ptr<Attribute>;

class NekoDeliverySession
{
protected:
	std::unique_ptr<NekoDeliverySessionDao> sessionDao;
public:
	NekoDeliverySession();
	/// <summary>
	/// �½�һ���Ự
	/// </summary>
	/// <param name="outSessionId">���ڱ������ɵ�sessionId</param>
	/// <param name="outSessionToken">���ڱ������ɵ�sessionToken</param>
	/// <param name="expiredTime">����ʱ�䣬����Ϊ��λ��Ĭ��Ϊһ����</param>
	/// <returns>�Ƿ񴴽��ɹ�</returns>
	/// <throws exception="SQLException">���ݿ������������ʱ�׳�</throws>
	bool createSession(unsigned long& outSessionId, std::string& outSessionToken, unsigned long expiredTime = 30 * 24 * 60 * 60 * 1000l) noexcept(false);

	/// <summary>
	/// ��ȡ�Ự������
	/// </summary>
	/// <param name="sessionId">�Ự��id</param>
	/// <param name="sessionToken">�Ự������</param>
	/// <returns>�Ự���ԡ���ȡʧ�ܷ���nullptr</returns>
	/// <throws exception-"SessionExpiredException">����Ự�ѹ������׳����쳣</throws>
	PtrAttribute getAttribute(unsigned long sessionId, std::string sessionToken) noexcept(false);

	/// <summary>
	/// ����Ự
	/// </summary>
	/// <param name="sessionId">�Ự��id</param>
	/// <param name="sessionToken">�Ự������</param>
	/// <param name="attribute">�Ự����</param>
	/// <returns>�Ƿ񱣴�ɹ�</returns>
	/// <throws exception="SQLException">���ݿ������������ʱ�׳�</throws>
	bool saveAttribute(unsigned long sessionId, std::string sessionToken, Attribute& attribute) noexcept(false);
};