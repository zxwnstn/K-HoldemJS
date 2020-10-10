#pragma once

#include "SubComponent/MockChip.h"
#include "SubComponent/MockCard.h"

#include <vector>
#include <string>

namespace Mock {

	struct Player
	{
		using ID = std::string;

		Player(const ID& id, uint32_t chipCount = 300)
			: Chips(chipCount)
		{
		}

		bool Bet(Chip chip)
		{
			return true;
		}

		bool Rasie(Chip chip)
		{
			return true;
		}

		void Check()
		{
		}

		void Fold()
		{
		}

		void Reward(Chip chip)
		{
			Chips.Count += chip.Count;
		}

		Chip Chips;
		ID Id;
		std::vector<Card> Hands;
	};

}