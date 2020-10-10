#pragma once

#include "Player/MockPlayer.h"
#include "Deck/MockDeck.h"
#include "Board/MockBoard.h"
#include "SubComponent/MockEvent.h"
#include "MockEntity.h"

namespace Mock {

	struct Room
	{
		Room()
			: EventProc(this), Deck(reg), Board(reg)
		{
		}

		struct RoomEventProcedure
		{
			RoomEventProcedure(Room* room)
				: room(room)
			{
			}

			void Recive(Event* event)
			{
				Decode(event);
				Dispatch(event);
			}

			void Decode(Event* event)
			{

			}


			void Dispatch(Event* event)
			{

			}

			Room* room;
		};
		
		bool Join(unsigned int ID)
		{
			return true;
		}
		
		entt::registry reg;
		Entity Deck;
		Entity Board;
		std::vector<Entity> Players;
		RoomEventProcedure EventProc;
	};

}