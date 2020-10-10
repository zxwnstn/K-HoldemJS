#include "Room.h"

namespace Core {
	
	Room::Room()
		: EventProc(this), Deck(reg), Board(reg)
	{
		auto deckHands = Deck.AttachComponenet<Hand<52>>();
		for (unsigned int i = 0; i < 52; ++i)
		{
			deckHands.TakeCard(i);
		}
		deckHands.Shuffle();

		Board.AttachComponenet<Chip>(0);
		Board.AttachComponenet<Hand<5>>();

		std::cout << "Room이 생성 되었습니다\n";
	}

	Entity Room::createEntity()
	{
		Entity entity(reg);
		return entity;
	}

	Entity Room::deleteEntity(Entity & entity)
	{
		reg.destroy(entity.Handle);
	}

	bool Room::Join(Player & player)
	{
		auto find = Players.find(player.Id);

		if (find != Players.end())
		{
			std::cout << "중복된 아이디 입니다\n";
			return false;
		}
		std::cout << player.Id.data() << "님이 입장하셧습니다.\n";

		auto playerEntity = createEntity();

		playerEntity.AttachComponenet<Chip>(player.Money);
		if (player.IsHost)
		{
			playerEntity.AttachComponenet<Host>();
		}

		Players.insert({ player.Id, playerEntity });
		return true;
	}

	bool Room::Leave(Player & player)
	{
		ID id = player.Id;
		auto find = Players.find(id);

		if (find == Players.end())
		{
			std::cout << "접속되지 않은 플레이어 입니다\n";
			return false;
		}

		deleteEntity(find->second);
		Players.erase(find);
		return true;

	}
}


