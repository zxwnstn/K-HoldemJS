#include "pch.h"

#include "MockDeck.h"

TEST(Deck, GetCard)
{
	Obj(Deck) deck;
	
	auto prev_pureNo = deck.GetCard().PureNo;
	auto none = NoneCard.PureNo;
	for (int i = 0; i < 51; ++i)
	{
		auto cur_pureNo = deck.GetCard().PureNo;
		EXPECT_NE(prev_pureNo, none);
		EXPECT_NE(prev_pureNo, cur_pureNo);
		prev_pureNo = cur_pureNo;
	}

	EXPECT_EQ(deck.GetCard().PureNo, none);
}

TEST(Deck, Reset)
{
	Obj(Deck) deck;
	for (int i = 0; i < 52; ++i)
	{
		deck.GetCard();
	}
	deck.Reset();
	EXPECT_NE(deck.GetCard().PureNo, NoneCard.PureNo);
}

TEST(Deck, CardCount)
{
	Obj(Deck) deck;
	EXPECT_EQ(deck.GetCardCount(), deck.MaxCardCount);

	int drawCount = 34;
	for (int i = 0; i < drawCount; ++i)
	{
		deck.GetCard();
	}

	EXPECT_EQ(deck.GetCardCount(), deck.MaxCardCount - drawCount);
}