#include <tinyHttpd/tinyHttpd.h>
#include "../dao/user/NekoDeliveryUserDao.h"
#include "../dao/user/impl/NekoDeliveryUserDaoImpl.h"

class NekoDeliveryAuth : public TinyHttpd
{
private: 
	std::string apiPrefix = "/api/v1/auth";
	std::unique_ptr<NekoDeliveryUserDao> userDao;

public:
	NekoDeliveryAuth();

	void HTTPPacketHandler(int clientfd, HTTPPacket::HTTPRequestPacket request) noexcept;

private:
	/// <summary>
	/// 检查手机号是否已被注册
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket checkPhone(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// 发送注册验证码
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket sendRegisterSMG(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// 发送重置密码验证码
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket sendRecoverSMG(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// 注册账号
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket registerAccount(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// 登录账号
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket loginAccount(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// 重置密码
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket resetPassword(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// 更新用户信息
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket updateDetail(HTTPPacket::HTTPRequestPacket request) noexcept;

private:
	bool checkPhoneFormat(std::string phone) noexcept;
	bool checkPasswordFormat(std::string password) noexcept;
};

