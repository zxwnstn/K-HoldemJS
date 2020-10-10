#include "Player.h"

#include "Room.h"

namespace Core {

	Room* Player::RequestCreateRoom()
	{
		if (false)
		{
			return nullptr;
		}
		auto room = new Room;

		IsHost = true;
		room->Join(*this);

		return room;
	}


}



