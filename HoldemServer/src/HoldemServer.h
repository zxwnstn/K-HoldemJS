#pragma once

#include "TCP/tcp.h"
#include "Thread/Pool.h"

class HoldemServer
{
public:
	HoldemServer() = default;
	void Run();

	ThreadPool Services;
	Tcp::ServerSocket m_ServerSocket;
};