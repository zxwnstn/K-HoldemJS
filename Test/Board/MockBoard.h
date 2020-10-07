#pragma once

#include "SubComponent/MockCard.h"
#include "SubComponent/MockChip.h"

#include <Array>

namespace Mock {

	struct Board
	{
		Board()
			: AccumChips(0), Cards{52, 52, 52, 52, 52 }
		{
		}

		Chip AccumChips;
		std::array<Card, 5> Cards;
	};

}