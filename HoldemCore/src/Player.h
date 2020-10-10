#pragma once

#include <string>

namespace Core {

	using ID = std::string;
	struct Player
	{

		Player(const ID& id, int money = 0)
			: Id(id), Money(money)
		{
		}

		class Room* RequestCreateRoom();

		ID Id;
		bool IsHost = false;
		unsigned int Money;
	};

}
