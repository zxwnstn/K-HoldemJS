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
		playerEntity.AttachComponenet<Controller>();
		playerEntity.GetComponent<ConsoleSprite>() << "ID : " << player.Id << "\n";

		ConsoleRenderer::Draw(player.Id + "님이 입장하셧습니다.");

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
		auto& deck = ThisRoom.Deck.GetComponent<Hand<52>>();
		deck.Shuffle();
		deck.ResetPtr();

		auto& boardHand = ThisRoom.Board.GetComponent<Hand<5>>();
		boardHand.Vacate();

		PlayerIterator = ThisRoom.Players.begin();
	}

	Room::GameProcess::Phase Room::GameProcess::UpdateState()
	{
		if (CurPhase != Phase::Clear)
		{
			progPhase();
		}
		else
		{
			progClear();
		}
		PauseProc();

		return ++CurPhase;
	}

	void Room::GameProcess::update(delta_type delta, void * anotherData)
	{
		while (UpdateState() != Phase::End);
		succeed();
	}

	void Room::GameProcess::PauseProc()
	{
		system("pause");
	}

	void Room::GameProcess::progPhase()
	{
		ConsoleRenderer::ClearConsole();
		ConsoleRenderer::Draw(ToString(CurPhase) + "를 시작합니다");
		
		auto& boardHand = ThisRoom.Board.GetComponent<Hand<5>>();

		switch (CurPhase)
		{
		case Phase::PreFlop:
			for (auto& e : ThisRoom.Players)
			{
				auto player = e.second;
				auto& playerHand = player.GetComponent<Hand<2>>();
				FillCard(playerHand, 2);
			}
			break;
		case Phase::Flop:
			FillCard(boardHand, 3);
			break;
		default:
			FillCard(boardHand, 1);
			break;
		}

	#ifdef _DEBUG
		RenderDeckHand();
	#endif

		RenderBoardHand();
		RenderPlayerHand();

		progBetting();
	}

	void Room::GameProcess::progClear()
	{
		ConsoleRenderer::ClearConsole();
		ConsoleRenderer::Draw("----게임을 정산합니다----");

		for (auto it : ThisRoom.Players)
		{
			auto& player = it.second;
			auto& playerHand = player.GetComponent<Hand<2>>();
			playerHand.Vacate();
		}
	}

	void Room::GameProcess::RenderDeckHand()
	{
		auto& deckHand = ThisRoom.Deck.GetComponent<Hand<52>>();
		auto& csprite = ThisRoom.Deck.GetComponent<ConsoleSprite>();
		csprite.Clear();
		csprite(deckHand);
		ConsoleRenderer::Draw(csprite);
	}

	void Room::GameProcess::RenderPlayerHand()
	{
		for (auto it : ThisRoom.Players)
		{
			auto& player = it.second;
			auto& csprite = player.GetComponent<ConsoleSprite>();
			auto& playerHand = player.GetComponent<Hand<2>>();
			csprite.Clear();
			csprite << it.first;
			csprite(playerHand);
			ConsoleRenderer::Draw(csprite);
		}
	}

	void Room::GameProcess::RenderBoardHand()
	{
		auto& boardHand = ThisRoom.Board.GetComponent<Hand<5>>();
		auto& csprite = ThisRoom.Board.GetComponent<ConsoleSprite>();
		csprite.Clear();
		csprite(boardHand);
		ConsoleRenderer::Draw(csprite);
	}

	void Room::GameProcess::progBetting()
	{
		while (BettingDone) 
		{
			ConsoleRenderer::Draw(PlayerIterator->first + "님의 차례입니다 가능한 액션을 선택해 주세요!");
			auto curPlayer = PlayerIterator->second;

			auto curPlayerController = curPlayer.GetComponent<Controller>();
			curPlayerController.Exec();

			PlayerIterator++;
			if (PlayerIterator == ThisRoom.Players.end())
			{
				PlayerIterator = ThisRoom.Players.begin();
				break;
			}
		}
	}

}


