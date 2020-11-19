#include "NekoDeliveryAuth.h"
#include <iostream>
#include <arpa/inet.h>

void NekoDeliveryAuth::HTTPPacketHandler(int clientfd, HTTPPacket::HTTPRequestPacket request) noexcept
{
	HTTPPacket::HTTPResponsePacket response;
	response.responseHeaders.insert({ "Server", "nekoHttpd" });

	if (request.requestPath == "/hello")
	{
		response.SetResponseCode(HTTPPacket::ResponseCode::OK);
		response.body = "Hello!<br>You are requesting: " + request.requestPath;
		response.SetContentType("text/html;charset=UTF-8");
		connectedClients[clientfd].writeBuffer = response.ToString();
	}
	else
	{
		response.SetResponseCode(HTTPPacket::ResponseCode::OK);
		response.body = "Your request is hooked!<br>You are requesting: " + request.requestPath;
		response.SetContentType("text/html;charset=UTF-8");
		connectedClients[clientfd].writeBuffer = response.ToString();
	}
	char* addr = new char[INET_ADDRSTRLEN + 1]();
	std::cout << "Connected from: " << inet_ntop(AF_INET, &connectedClients[clientfd].clientInfo.sin_addr, addr, INET_ADDRSTRLEN) << " "
		      << "request path: " << request.requestPath << std::endl;
	delete[] addr;
}
