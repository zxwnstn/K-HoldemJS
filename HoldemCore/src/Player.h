#pragma once

using ID = std::string;

namespace Core {

	struct Player
	{

		Player(ID id, unsigned int money = 0)
			: Id(id), Money(money)
		{
		}

		class Room* RequestCreateRoom();

		ID Id;
		bool IsHost = false;
		unsigned int Money;
	};

}
