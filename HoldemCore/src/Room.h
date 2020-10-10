#include "Entity.h"

#include "Player.h"
#include "SubComponent.h"

namespace Core {

	struct Room
	{
		using Host = entt::tag<"Host"_hs>;
		
	private:
		struct GameProcess : entt::process<GameProcess, std::uint32_t>
		{

		};

		struct RoomEventProcedure 
		{
			RoomEventProcedure(Room* room)
				: room(room)
			{
			}

			/*void Recive(Event* event)
			{
				Decode(event);
				Dispatch(event);
			}

			void Decode(Event* event)
			{

			}

			void Dispatch(Event* event)
			{

			}*/

			Room* room;
		};

	public:
		Room();

		bool Join(Player& player);
		bool Leave(Player& player);

	private:
		Entity createEntity();
		Entity deleteEntity(Entity& entity);

	private:
		entt::registry reg;

		Entity Deck;
		Entity Board;

		entt::scheduler<uint32_t> GameProcess;
		std::unordered_map<ID, Entity> Players;
		RoomEventProcedure EventProc;
	};

	

}

