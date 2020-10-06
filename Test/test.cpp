#include <gtest/gtest.h>

#include "Hellow.h"
#include "SomeStruct.h"

#include <vector>
#include <algorithm>
#include <string.h>
#include <random>
#include <entt.hpp>

struct Mock_Deck
{
	Mock_Deck()
		: deck(52)
	{
		for (int i = 0; i < 52; ++i)
		{
			deck[i] = i + 1;
		}
		Reset();
	}
	std::vector<int> deck;

	int GetCard()
	{
		if (cardPtr < 52)
		{
			return deck[cardPtr++];
		}
		else
		{
			return -1;
		}
	}

	void Reset()
	{
		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(deck.begin(), deck.end(), g);
		cardPtr = 0;
	}

	int cardPtr = 0;
};


struct Mock_Board
{
	Mock_Board()
	{
	}

	bool DrawCard()
	{
		
		if (drawCount == 0)
		{
			for (int i = 0; i < 3; ++i)
			{
				cardSlot[i] = deck.GetCard();
			}
		}
		else if (drawCount == 1)
		{
			cardSlot[3] = deck.GetCard();
		}
		else if(drawCount == 2)
		{
			cardSlot[4] = deck.GetCard();
		}
		else
		{
			return false;
		}
		drawCount++;
		return true;
	}

	int GetCardCount()
	{
		int ret = 0;
		for (int i = 0; i < 5; ++i)
		{
			if (cardSlot[i] == 0)
				break;
			ret++;
		}
		return ret;
	}

	int GetAcumChilps() const
	{
		return chips;
	}

	void Reset()
	{
		drawCount = 0;
		memset(cardSlot, 0, sizeof(cardSlot));
	}

	struct Mock_Player
	{
		void Race(int chipCount)
		{
			curBoard->chips += chipCount;
		}
		Mock_Board* curBoard;
	};

	void Join(Mock_Player* player)
	{
		player->curBoard = this;
	}

	Mock_Deck deck;
	int drawCount = 0;
	int cardSlot[5]{ 0 };
	int chips = 0;
};



TEST(Deck, GetCard)
{
	Mock_Deck deck;
	for (int i = 0; i < 52; ++i)
	{
		EXPECT_TRUE(deck.GetCard() != -1);
	}
	EXPECT_TRUE(deck.GetCard() == -1);
	deck.Reset();
	EXPECT_TRUE(deck.GetCard() != -1);
}

TEST(Board, GetCardCount)
{
	Mock_Board board;
	
	board.DrawCard();
	EXPECT_TRUE(board.GetCardCount() == 3);
	board.DrawCard();				 
	EXPECT_TRUE(board.GetCardCount() == 4);
	board.DrawCard();				 
	EXPECT_TRUE(board.GetCardCount() == 5);
}

TEST(Board, DrawCard)
{
	Mock_Board board;

	EXPECT_TRUE(board.DrawCard());
	EXPECT_TRUE(board.DrawCard());
	EXPECT_TRUE(board.DrawCard());
	EXPECT_FALSE(board.DrawCard());

	board.Reset();
	EXPECT_TRUE(board.DrawCard());
	EXPECT_TRUE(board.DrawCard());
	EXPECT_TRUE(board.DrawCard());
	EXPECT_FALSE(board.DrawCard());
}

TEST(Board, Race)
{
	Mock_Board board;
	Mock_Board::Mock_Player player1;
	Mock_Board::Mock_Player player2;

	board.Join(&player1);
	board.Join(&player2);

	player1.Race(10);
	EXPECT_TRUE(board.GetAcumChilps() == 10);
	player2.Race(20);
	EXPECT_TRUE(board.GetAcumChilps() == 30);
	player1.Race(30);
	EXPECT_TRUE(board.GetAcumChilps() == 60);
	player2.Race(0);
	EXPECT_TRUE(board.GetAcumChilps() == 60);
}


TEST(Entt, CompoenentCheck)
{
	entt::registry reg;
	auto entity = reg.create();

	reg.emplace<Mock_Deck>(entity);

	auto& deck = reg.get<Mock_Deck>(entity);

	EXPECT_TRUE(deck.GetCard() != -1);
}

TEST(Entt, CompoenentView)
{
	entt::registry reg;
	auto entity = reg.create();

	reg.emplace<Mock_Board::Mock_Player>(entity);
	reg.emplace<Mock_Deck>(entity);

	auto view = reg.view<Mock_Deck>();

	for (auto& entity : view)
	{
		auto deck = view.get<Mock_Deck>(entity);
		EXPECT_TRUE(deck.GetCard() != -1);
	}
}