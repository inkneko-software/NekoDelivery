#include "NekoDeliveryAuth.h"

int main()
{
	NekoDeliveryAuth authModule;
	authModule.Init("/etc/neko_delivery/auth.conf");
	authModule.StartListen();
	authModule.StartHandleRequest();
	return 0;
}