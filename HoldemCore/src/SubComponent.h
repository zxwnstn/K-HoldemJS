#pragma once

#include "pch.h"

#include "RenderingComponenet.h"

namespace Core {

	struct Chip
	{
		Chip()
			: Count(0)
		{}

		Chip(unsigned int count)
			: Count(count)
		{
		}

		void DrawContext(ConsoleSprite& csprite)
		{
			csprite.stream << Count << "\n";
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

		void DrawContext(ConsoleSprite& csprite)
		{
			if (PureNo == 52)
				return;

			switch (Spec.Shape)
			{
			case CardShape::Spade:
				csprite.stream << "Spade";
				break;
			case CardShape::Diamond:
				csprite.stream << "Diamond";
				break;
			case CardShape::Heart:
				csprite.stream << "Heart";
				break;
			case CardShape::Clover:
				csprite.stream << "Clover";
				break;
			}

			auto number = static_cast<unsigned int>(Spec.Number);
			switch (number)
			{
			case 0:
				csprite.stream << "A";
				break;
			case 10:
				csprite.stream << "J";
				break;
			case 11:
				csprite.stream << "Q";
				break;
			case 12:
				csprite.stream << "K";
				break;
			default:
				csprite.stream << number + 1;
				break;
			}
			csprite.stream << "  \t";
		}

		CardSpec Spec;
		unsigned int PureNo = 52;
	};
	#define NoneCard Core::Card(52)

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

		void ResetPtr()
		{
			cardPtr = 0;
		}

		void Vacate()
		{
			Hands.fill(NoneCard);
		}

		Card BringCard()
		{
			return Hands[cardPtr++];
		}

		void DrawContext(ConsoleSprite& csprite)
		{
			switch (Max)
			{
			case 2:
				csprite.stream << "플레이어 핸드\n";
			case 5:
				csprite.stream << "보드의 카드\n";
			case 52:
				csprite.stream << "덱 리스트\n";
			}
			for (int i = 0; i < Max; ++i)
			{
				Hands[i].DrawContext(csprite);
				if (i % 6 == 5)
				{
					csprite.stream << "\n";
				}
			}
			csprite.stream << "\n";
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

	
}
