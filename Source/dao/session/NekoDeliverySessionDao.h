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
	/// 保存会话令牌信息
	/// </summary>
	/// <param name="sessionToken">指定的会话令牌信息</param>
	/// <returns>是否保存成功。如果保存成功，会将session_id保存到sessionToken中</returns>
	virtual bool saveSessionToken(SessionToken& sessionToken) = 0;

	/// <summary>
	/// 查询指定的会话令牌信息。通过绑定会话id-会话令牌保证令牌不会冲突
	/// </summary>
	/// <param name="sessionId">会话id</param>
	/// <param name="sessionToken">会话令牌</param>
	/// <returns>匹配的会话令牌。未查询到返回nullptr</returns>
	virtual PtrSessionToken getSessionToken(unsigned long sessionId, std::string sessionToken) = 0;

	/// <summary>
	/// 更新会话令牌信息
	/// </summary>
	/// <param name="sessionToken">指定的会话令牌</param>
	/// <returns>是否更新成功</returns>
	virtual bool updateSessionToken(const SessionToken& sessionToken) = 0;

	/// <summary>
	/// 保存会话属性
	/// </summary>
	/// <param name="sessionProperites">会话属性</param>
	/// <returns>是否保存成功</returns>
	virtual bool saveSessionProperties(const SessionProperties& sessionProperites) = 0;

	/// <summary>
	/// 查询会话属性
	/// </summary>
	/// <param name="sessionId">指定的会话id</param>
	/// <returns>会话属性。未查询到返回nullptr</returns>
	virtual PtrSessionProperties getSessionProperties(unsigned long sessionId) = 0;

	/// <summary>
	/// 更新会话属性
	/// </summary>
	/// <param name="sessionProperties">会话属性</param>
	/// <returns>是否更新成功</returns>
	virtual bool updateSessionProperties(const SessionProperties& sessionProperties) = 0;

	virtual ~NekoDeliverySessionDao() {};
};