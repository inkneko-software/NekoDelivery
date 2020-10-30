#include <tinyHttpd/tinyHttpd.h>
#include <iostream>
#include <signal.h>
TinyHttpd server;
void sigterm(int signal)
{
	server.~TinyHttpd();
	exit(0);
}

int main(int argc, char **argv)
{
	signal(SIGTERM, sigterm);
	signal(SIGINT, sigterm);
	signal(SIGKILL, sigterm);

	using namespace std;
	try
	{
		server.Init();
		server.LoadMIME();
		server.StartListen();
		server.DumpProperty();
	}
	catch (std::runtime_error e)
	{
		cout << "Server init error: " << e.what() << endl;
		return -1;
	}
	
	cout << "Server start running." << endl;
	server.StartHandleRequest();

	return 0;
}
