#pragma once

#include "pch.h"

struct Chip
{
	Chip()
		: Count(0)
	{}

	Chip(unsigned int count)
		: Count(count)
	{
	}

	unsigned int Count;
};

enum class CardNumber
{
	_A, _2, _3, _4, _5, _6, _7, _8, _9, _10,
	_J, _Q, _K, None
};

enum class CardShape
{
	Spade, Diamond, Heart, Clover, None
};

struct Card
{
	struct CardSpec
	{
		CardNumber Number = CardNumber::None;
		CardShape Shape = CardShape::None;
	};

	Card()
	{
	}

	Card(int pureNo)
	{
		if (0 <= pureNo && pureNo < 52)
		{
			Spec.Number = static_cast<CardNumber>(pureNo % 13);
			Spec.Shape = static_cast<CardShape>(pureNo / 13);
			PureNo = pureNo;
		}
	}

	CardSpec Spec;
	unsigned int PureNo = 52;
};
#define NoneCard Mock::Card(52)

template<unsigned int Max = 2>
struct Hand
{
	Hand()
		: cardPtr(0)
	{
	}

	void TakeCard(const Card& card)
	{
		Hands[cardPtr++] = card;
	}

	void Reset()
	{
		cardPtr = 0;
	}

	void Shuffle()
	{
		if (Max != 52)
		{
			return;
		}
		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(Hands.begin(), Hands.end(), g);
	}
 
	unsigned int cardPtr;
	std::array<Card, Max> Hands;
};