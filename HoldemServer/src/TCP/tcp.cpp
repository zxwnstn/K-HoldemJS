#include "pch.h"

#include "tcp.h"

namespace Tcp {

	Socket::Socket(const IPv4 & Ip)
	{
		m_Socket = socket(PF_INET, SOCK_STREAM, 0);

		m_Address.sin_family = AF_INET;
		m_Address.sin_addr.S_un.S_addr = Ip;
		m_Address.sin_port = STATIC_PORT;

		bind(m_Socket, (SOCKADDR*)&m_Address, sizeof(SOCKADDR_IN));
	}

	Socket::~Socket()
	{
		closesocket(m_Socket);
	}

	void ClientSocket::Connect(const IPv4 & Ip)
	{
		m_Address.sin_family = AF_INET;
		m_Address.sin_addr.S_un.S_addr = Ip;
		m_Address.sin_port = STATIC_PORT;

		connect(m_Socket, (SOCKADDR*)&m_Address, sizeof(SOCKADDR_IN));
	}

	void ClientSocket::Send(const Packet& packet)
	{
		send(m_Socket, packet.SerialziedData, packet.Length, 0);
	}

	Packet ClientSocket::Recieve()
	{
		Packet packet;
		recv(m_Socket, packet.SerialziedData, BUFFER_MAX, 0);

		return packet;
	}

	Socket ServerSocket::Accept()
	{
		Socket Client;
		listen(m_Socket, SOMAXCONN);
		Client.m_Socket = accept(m_Socket, (SOCKADDR*)&Client.m_Address, nullptr);

		return Client;
	}
}



