#pragma once

struct Packet
{
	uint32_t  Length;
	char SerialziedData[BUFFER_MAX];
};