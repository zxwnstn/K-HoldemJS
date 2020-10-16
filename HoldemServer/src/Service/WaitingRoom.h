#pragma once

namespace Service {

	struct WRData
	{

	};


	std::any analysisPacket(Packet& packet)
	{

		return 3;
	}

	WRData WaitigProc(Tcp::Socket& client)
	{
		Packet packet;

		while (recv(client, packet.SerialziedData, BUFFER_MAX, 0))
		{

		}
	}

	WRData LogIn(Tcp::Socket& client)
	{
		//TODO : Send to client connected server
		Packet packet;

		while (1)
		{
			recv(client, packet.SerialziedData, BUFFER_MAX, 0);
			auto logInData = analysisPacket(packet);

			bool approval = QueryDB(logInData);

		}

	}

}