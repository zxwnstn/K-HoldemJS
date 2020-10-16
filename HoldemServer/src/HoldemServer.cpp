#include "pch.h"
#include "HoldemServer.h"

#include "Service/WaitingRoom.h"

void HoldemServer::Run()
{
	while (true)
	{
		auto client = m_ServerSocket.Accept();
		Services.EnqueueJob(Service::LogIn, client);
	}
}
