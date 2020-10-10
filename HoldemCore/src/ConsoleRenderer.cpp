#include "ConsoleRenderer.h"

namespace Core {

	void ConsoleRenderer::Draw(const std::string & str, bool br)
	{
		std::cout << str;
		if (br)
		{
			std::cout << "\n";
		}
	}

	void ConsoleRenderer::Draw(const std::stringstream & sstr, bool br)
	{
		std::cout << sstr.str();
		if (br)
		{
			std::cout << "\n";
		}
	}

	void ConsoleRenderer::Draw(const ConsoleSprite & csprite, bool br)
	{
		Draw(csprite.stream);
	}

	void ConsoleRenderer::ClearConsole()
	{
		system("cls");
	}

	void ConsoleRenderer::BeginScene()
	{
		ClearConsole();
	}

	void ConsoleRenderer::EndScene()
	{
		std::cout.flush();
	}

}

