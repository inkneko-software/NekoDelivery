#include <tinyHttpd/tinyHttpd.h>

class NekoDeliveryAuth : public TinyHttpd
{
public:
	void HTTPPacketHandler(int clientfd, HTTPPacket::HTTPRequestPacket request) noexcept;
};

