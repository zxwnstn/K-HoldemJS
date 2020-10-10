#include "Core.h"

int main()
{
	Core::Player zxwnstn("zxwnstn", 2000u);
	Core::Player kiseop("kiseop", 2000u);

	auto room = zxwnstn.RequestCreateRoom();

	room->Join(kiseop);

	while (1)
	{
		char GoGame;
		std::cout << "Run Game? (Y/N) ";
		std::cin >> GoGame;
		if (GoGame == 'n' || GoGame == 'N')
			break;
		room->StartGame();
		system("cls");
	}

	room->Leave(zxwnstn);
	room->Leave(kiseop);
}