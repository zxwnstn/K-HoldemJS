#pragma once

#include "SubComponent/MockCard.h"
#include <vector>

namespace Mock {

	struct Deck
	{
		Deck()
			: CardCount(MaxCardCount)
		{
			Cards.reserve(MaxCardCount);
			for (int i = 0; i < 52; ++i)
			{
				Cards.emplace_back(i);
			}
			Reset();
		}

		Card GetCard()
		{
			Card ret = NoneCard;
			if (CurCard != Cards.end())
			{
				--CardCount;
				ret = *CurCard;
				CurCard++;
			}
			return ret;
		}

		void Reset()
		{
			/*
				Require : implement shuffle
			*/
			CardCount = 52;
			CurCard = Cards.begin();
		}

		unsigned int GetCardCount() const
		{
			return CardCount;
		}

		const unsigned int MaxCardCount = 52;
		unsigned int CardCount;
		std::vector<Card>::iterator CurCard;
		std::vector<Card> Cards;
	};

}
