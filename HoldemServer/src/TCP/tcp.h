#pragma once

#include "IPv4.h"
#include "Packet.h"

namespace Tcp {

	class Socket
	{
	public:
		Socket(const IPv4& Ip);
		Socket() = default;
		~Socket();

		inline operator SOCKET() const { return m_Socket; }

		SOCKET m_Socket = 0;
		SOCKADDR_IN m_Address{ 0, };
	};


	class ClientSocket : public Socket
	{
		ClientSocket() = default;
		void Connect(const IPv4& Ip);

		void Send(const Packet& packet);
		Packet Recieve();
	};


	class ServerSocket : public Socket
	{
	public:
		ServerSocket()
			: Socket(IPv4::Create())
		{}

		Socket Accept();
	};

}
