#include "pch.h"

#include "WSA.h"

static WSADATA s_WsaData;

void WSA::Init(uint16_t Version)
{
	static bool isInit = false;

	if (isInit)
	{
		return;
	}

	WSAStartup(Version, &s_WsaData);
}

void WSA::ShutDown()
{
	WSACleanup();
}
