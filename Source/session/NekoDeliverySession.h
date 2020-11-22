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
	/// 新建一个会话
	/// </summary>
	/// <param name="outSessionId">用于保存生成的sessionId</param>
	/// <param name="outSessionToken">用于保存生成的sessionToken</param>
	/// <param name="expiredTime">过期时间，以秒为单位。默认为一个月</param>
	/// <returns>是否创建成功</returns>
	/// <throws exception="SQLException">数据库操作发生错误时抛出</throws>
	bool createSession(unsigned long& outSessionId, std::string& outSessionToken, unsigned long expiredTime = 30 * 24 * 60 * 60 * 1000l) noexcept(false);

	/// <summary>
	/// 获取会话的属性
	/// </summary>
	/// <param name="sessionId">会话的id</param>
	/// <param name="sessionToken">会话的令牌</param>
	/// <returns>会话属性。获取失败返回nullptr</returns>
	/// <throws exception-"SessionExpiredException">如果会话已过期则抛出本异常</throws>
	PtrAttribute getAttribute(unsigned long sessionId, std::string sessionToken) noexcept(false);

	/// <summary>
	/// 保存会话
	/// </summary>
	/// <param name="sessionId">会话的id</param>
	/// <param name="sessionToken">会话的令牌</param>
	/// <param name="attribute">会话属性</param>
	/// <returns>是否保存成功</returns>
	/// <throws exception="SQLException">数据库操作发生错误时抛出</throws>
	bool saveAttribute(unsigned long sessionId, std::string sessionToken, Attribute& attribute) noexcept(false);
};