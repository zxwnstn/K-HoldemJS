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

		ConsoleRenderer::Draw("Holdem Room�� ���� �Ǿ����ϴ�\n");
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
			ConsoleRenderer::Draw("�ߺ��� ���̵� �Դϴ�");
			return false;
		}

		auto playerEntity = createEntity();

		playerEntity.AttachComponenet<Chip>(player.Money);
		playerEntity.AttachComponenet<Hand<2>>();
		playerEntity.AttachComponenet<ConsoleSprite>();
		playerEntity.GetComponent<ConsoleSprite>() << "ID : " << player.Id << "\n";

		ConsoleRenderer::Draw(player.Id  + "���� �����ϼ˽��ϴ�.");

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
			ConsoleRenderer::Draw("���ӵ��� ���� �÷��̾� �Դϴ�");
			return false;
		}

		ConsoleRenderer::Draw(player.Id + "���� �����ϼ˽��ϴ�.");
		deleteEntity(find->second);


		Players.erase(find);
		return true;

	}
	bool Room::StartGame()
	{
		if (Players.size() == 1)
		{
			ConsoleRenderer::Draw("������ �����ϱ⿡ ����� �ο��� �������� �ʾҽ��ϴ�!");
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
			progPreFlop();
			break;
		case Phase::Flop:
			progFlop();
			break;
		case Phase::Turn:
			progTurn();
			break;
		case Phase::River:
			progRiver();
			break;
		case Phase::Clear:
			progClear();
			break;
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

	void Room::GameProcess::progPreFlop()
	{
		ConsoleRenderer::ClearConsole();
		ConsoleRenderer::Draw("PreFlop�� �����մϴ�");

		//distribute Card
		for (auto it : ThisRoom.Players)
		{
			auto& player = it.second;
			auto& playerHand = player.GetComponent<Hand<2>>();
			FillCard(playerHand, 2);
		}

	#ifdef _DEBUG
		RenderDeckHand();
	#endif
		RenderPlayerHand();

		progBetting();
	}

	void Room::GameProcess::progFlop()
	{
		ConsoleRenderer::ClearConsole();
		ConsoleRenderer::Draw("Flop�� �����մϴ�");

		auto& deck = ThisRoom.Deck.GetComponent<Hand<52>>();
		auto& boardHand = ThisRoom.Board.GetComponent<Hand<5>>();

		FillCard(boardHand, 3);

		RenderBoardHand();
		RenderPlayerHand();

		progBetting();

		system("pause");
	}

	void Room::GameProcess::progTurn()
	{
		ConsoleRenderer::ClearConsole();
		ConsoleRenderer::Draw("Turn�� �����մϴ�");

		progBetting();

		system("pause");
	}

	void Room::GameProcess::progRiver()
	{
		ConsoleRenderer::ClearConsole();
		ConsoleRenderer::Draw("River�� �����մϴ�");

		progBetting();

		system("pause");
	}

	void Room::GameProcess::progClear()
	{
		ConsoleRenderer::ClearConsole();
		ConsoleRenderer::Draw("----������ �����մϴ�----");

		for (auto it : ThisRoom.Players)
		{
			auto& player = it.second;
			auto& playerHand = player.GetComponent<Hand<2>>();
			playerHand.Vacate();
		}

		system("pause");
	}

	void Room::GameProcess::RenderDeckHand()
	{
		auto& deckHand = ThisRoom.Deck.GetComponent<Hand<52>>();
		auto& csprite = ThisRoom.Deck.GetComponent<ConsoleSprite>();
		csprite.Clear();
		csprite(deckHand);
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
			//playerHand.DrawContext(csprite);
			ConsoleRenderer::Draw(csprite);
		}
	}

	void Room::GameProcess::RenderBoardHand()
	{
		auto& boardHand = ThisRoom.Board.GetComponent<Hand<5>>();
		auto& csprite = ThisRoom.Board.GetComponent<ConsoleSprite>();
		csprite.Clear();
		//boardHand.DrawContext(csprite);
		ConsoleRenderer::Draw(csprite);
	}

	void Room::GameProcess::progBetting()
	{

	}
	
}


