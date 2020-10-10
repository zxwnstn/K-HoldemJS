#include "Room.h"

#include "ConsoleRenderer.h";

namespace Core {
	
	Room::Room()
		: EventProc(*this), Deck(reg), Board(reg)
	{
		Deck.AttachComponenet<Hand<52>>();
		Deck.AttachComponenet<ConsoleSprite>();

		auto& deckHands = Deck.GetComponent<Hand<52>>();
		for (unsigned int i = 0; i < 52; ++i)
		{
			deckHands.TakeCard(i);
		}

		Board.AttachComponenet<Chip>(0);
		Board.AttachComponenet<Hand<5>>();
		Board.AttachComponenet<ConsoleSprite>();

		ConsoleRenderer::Draw("Holdem Room이 생성 되었습니다\n");
	}

	Entity Room::createEntity()
	{
		Entity entity(reg);
		return entity;
	}

	bool Room::deleteEntity(Entity & entity)
	{
		reg.destroy(entity.Handle);
		return true;
	}

	bool Room::Join(const Player & player)
	{
		auto find = Players.find(player.Id);

		if (find != Players.end())
		{
			ConsoleRenderer::Draw("중복된 아이디 입니다");
			return false;
		}

		auto playerEntity = createEntity();

		playerEntity.AttachComponenet<Chip>(player.Money);
		playerEntity.AttachComponenet<Hand<2>>();
		playerEntity.AttachComponenet<ConsoleSprite>();
		playerEntity.GetComponent<ConsoleSprite>() << "ID : " << player.Id << "\n";

		ConsoleRenderer::Draw(player.Id  + "님이 입장하셧습니다.");

		if (player.IsHost)
		{
			playerEntity.AttachComponenet<Host>();
		}

		Players.emplace(player.Id, playerEntity);
		return true;
	}

	bool Room::Leave(Player & player)
	{
		auto id = player.Id;
		auto find = Players.find(id);

		if (find == Players.end())
		{
			ConsoleRenderer::Draw("접속되지 않은 플레이어 입니다");
			return false;
		}

		ConsoleRenderer::Draw(player.Id + "님이 퇴장하셧습니다.");
		deleteEntity(find->second);


		Players.erase(find);
		return true;

	}
	bool Room::StartGame()
	{
		if (Players.size() == 1)
		{
			ConsoleRenderer::Draw("게임을 시작하기에 충분한 인원이 갖춰지지 않았습니다!");
			return false;
		}

		Process.attach<GameProcess>(*this);
		Process.update(1u);
		return true;
	}

	Room::GameProcess::GameProcess(Room & thisRoom)
		: ThisRoom(thisRoom), CurPhase(Phase::PreFlop)
	{
		auto& deck = thisRoom.Deck.GetComponent<Hand<52>>();
		deck.Shuffle();
		deck.ResetPtr();

		auto& boardHand = thisRoom.Board.GetComponent<Hand<5>>();
		boardHand.Vacate();
	}

	Room::GameProcess::Phase Room::GameProcess::UpdateState()
	{
		switch (CurPhase)
		{
		case Phase::PreFlop:
			preFlop();
			return CurPhase = Phase::Flop;
		case Phase::Flop:
			flop();
			return CurPhase = Phase::Turn;
		case Phase::Turn:
			turn();
			return CurPhase = Phase::River;
		case Phase::River:
			river();
			return CurPhase = Phase::Clear;
		}
		clear();
		return Phase::End;
	}

	void Room::GameProcess::update(delta_type delta, void * anotherData)
	{
		while (UpdateState() != Phase::End);
		succeed();
	}

	void Room::GameProcess::preFlop()
	{
		ConsoleRenderer::ClearConsole();

		ConsoleRenderer::Draw("PreFlop을 시작합니다");
		auto& deck = ThisRoom.Deck.GetComponent<Hand<52>>();

	#ifdef _DEBUG
		auto& csprite = ThisRoom.Deck.GetComponent<ConsoleSprite>();
		csprite.Clear();
		deck.DrawContext(csprite);
		ConsoleRenderer::Draw(csprite);
	#endif

		for (auto it : ThisRoom.Players)
		{
			auto& player = it.second;
			player.GetComponent<Hand<2>>();

		}
		system("pause");
	}

	void Room::GameProcess::flop()
	{
		ConsoleRenderer::ClearConsole();
		ConsoleRenderer::Draw("Flop을 시작합니다");
		system("pause");
	}

	void Room::GameProcess::turn()
	{
		ConsoleRenderer::ClearConsole();
		ConsoleRenderer::Draw("Flop을 시작합니다");
		system("pause");
	}

	void Room::GameProcess::river()
	{
		ConsoleRenderer::ClearConsole();
		ConsoleRenderer::Draw("Rlop을 시작합니다");
		system("pause");
	}

	void Room::GameProcess::clear()
	{
		ConsoleRenderer::ClearConsole();
		ConsoleRenderer::Draw("----게임을 정산합니다----");
		system("pause");
	}
}


