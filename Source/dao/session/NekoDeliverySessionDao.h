#pragma once
#include "table/SessionToken.h"
#include "table/SessionProperties.h"

#include <memory>

using PtrSessionToken = std::unique_ptr<SessionToken>;
using PtrSessionProperties = std::unique_ptr<SessionProperties>;
class NekoDeliverySessionDao
{
public:
	/// <summary>
	/// ����Ự������Ϣ
	/// </summary>
	/// <param name="sessionToken">ָ���ĻỰ������Ϣ</param>
	/// <returns>�Ƿ񱣴�ɹ����������ɹ����Ὣsession_id���浽sessionToken��</returns>
	virtual bool saveSessionToken(SessionToken& sessionToken) = 0;

	/// <summary>
	/// ��ѯָ���ĻỰ������Ϣ��ͨ���󶨻Ựid-�Ự���Ʊ�֤���Ʋ����ͻ
	/// </summary>
	/// <param name="sessionId">�Ựid</param>
	/// <param name="sessionToken">�Ự����</param>
	/// <returns>ƥ��ĻỰ���ơ�δ��ѯ������nullptr</returns>
	virtual PtrSessionToken getSessionToken(unsigned long sessionId, std::string sessionToken) = 0;

	/// <summary>
	/// ���»Ự������Ϣ
	/// </summary>
	/// <param name="sessionToken">ָ���ĻỰ����</param>
	/// <returns>�Ƿ���³ɹ�</returns>
	virtual bool updateSessionToken(const SessionToken& sessionToken) = 0;

	/// <summary>
	/// ����Ự����
	/// </summary>
	/// <param name="sessionProperites">�Ự����</param>
	/// <returns>�Ƿ񱣴�ɹ�</returns>
	virtual bool saveSessionProperties(const SessionProperties& sessionProperites) = 0;

	/// <summary>
	/// ��ѯ�Ự����
	/// </summary>
	/// <param name="sessionId">ָ���ĻỰid</param>
	/// <returns>�Ự���ԡ�δ��ѯ������nullptr</returns>
	virtual PtrSessionProperties getSessionProperties(unsigned long sessionId) = 0;

	/// <summary>
	/// ���»Ự����
	/// </summary>
	/// <param name="sessionProperties">�Ự����</param>
	/// <returns>�Ƿ���³ɹ�</returns>
	virtual bool updateSessionProperties(const SessionProperties& sessionProperties) = 0;

	virtual ~NekoDeliverySessionDao() {};
};