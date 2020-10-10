#pragma once

#include <sstream>
#include <string>

namespace Core {

	struct ConsoleSprite
	{
		ConsoleSprite()
		{
		}


		std::stringstream& operator <<(const char* str)
		{
			stream << str;
			return stream;
		}

		std::stringstream& operator <<(const std::string& str)
		{
			stream << str;
			return stream;
		}
		
		void Clear()
		{
			stream.str("");
		}
		std::stringstream stream;
	};

}