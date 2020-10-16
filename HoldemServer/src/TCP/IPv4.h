#pragma once

class IPv4
{
public:
	static IPv4 Create(const std::string& ip)
	{
		return Create(ip.data());
	}

	static IPv4 Create(const char* ip)
	{
		return IPv4(inet_addr(ip));
	}

	//This Device
	static IPv4 Create()
	{
		return IPv4(htonl(INADDR_ANY));
	}

	static IPv4 Create(uint8_t A, uint32_t B, uint32_t C, uint32_t D)
	{
		A <<= 24;
		B <<= 16;
		C <<= 8;
		return IPv4(A + B + C + D);
	}

	operator ULONG() const
	{
		return Ip;
	}

private:
	IPv4(uint32_t Ip)
		: Ip{Ip}
	{}

	uint32_t Ip;
};

