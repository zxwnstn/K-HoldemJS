#include "pch.h"

#include "HoldemServer.h"
#include "TCP/WSA.h"

int main()
{
	WSA::Init(WINSOCK_VERSION_2_2);
	HoldemServer().Run();
	WSA::ShutDown();

	return 0;
}