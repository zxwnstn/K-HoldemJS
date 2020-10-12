#pragma once

#include <iostream>
#include <string>

namespace Core {

	class Input
	{
	public:
		static int GetInt()
		{
			int ret;
			std::cin >> ret;
			return ret;
		}

		static int GetClampInt(int min, int max)
		{
			int ret;
			while (true)
			{
				ret = GetInt();
				if (min <= ret && ret <= max)
				{
					break;
				}
				std::cout << "잘못된 입력입니다.";
			}
			return ret;
		}

		static uint32_t GetUint32()
		{
			uint32_t ret;
			std::cin >> ret;
			return ret;
		}

		static uint32_t GetClampUint32(uint32_t min, uint32_t max)
		{
			uint32_t ret;
			while (true)
			{
				ret = GetInt();
				if (min <= ret && ret <= max)
				{
					break;
				}
				std::cout << "잘못된 입력입니다.";
			}
			return ret;
		}

		static std::string GetString()
		{
			std::string ret;
			std::cin >> ret;
			return ret;
		}

		static char GetChar()
		{
			char ret;
			std::cin >> ret;
			return ret;
		}

	};

}
