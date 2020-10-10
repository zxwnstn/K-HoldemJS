#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include "RenderingComponenet.h"

namespace Core {

	class ConsoleRenderer
	{
	public:
		static void Draw(const std::string& str, bool br = true);
		static void Draw(const std::stringstream& sstr, bool br = true);
		static void Draw(const ConsoleSprite& csprite, bool br = true);

		static void ClearConsole();

		static void BeginScene();
		static void EndScene();

	};

}
