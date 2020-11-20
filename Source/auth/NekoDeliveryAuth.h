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
	/// ����ֻ����Ƿ��ѱ�ע��
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket checkPhone(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// ����ע����֤��
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket sendRegisterSMG(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// ��������������֤��
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket sendRecoverSMG(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// ע���˺�
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket registerAccount(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// ��¼�˺�
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket loginAccount(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket resetPassword(HTTPPacket::HTTPRequestPacket request) noexcept;
	/// <summary>
	/// �����û���Ϣ
	/// </summary>
	/// <param name="request"></param>
	/// <returns></returns>
	HTTPPacket::HTTPResponsePacket updateDetail(HTTPPacket::HTTPRequestPacket request) noexcept;

private:
	bool checkPhoneFormat(std::string phone) noexcept;
	bool checkPasswordFormat(std::string password) noexcept;
};

