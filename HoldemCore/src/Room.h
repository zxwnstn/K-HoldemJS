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
			enum class Phase 
			{
				PreFlop, Flop, Turn, River, Clear, End
			};
			
		private:
			void preFlop();
			void flop();
			void turn();
			void river();
			void clear();

		public:
			GameProcess(Room& thisRoom);

			Phase UpdateState();
			void update(delta_type delta, void* anotherData);

		private:
			Phase CurPhase;
			Room& ThisRoom;
		};

		struct RoomEventProcedure 
		{
			RoomEventProcedure(Room& room)
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

			Room& room;
		};

	public:
		Room();

		bool Join(const Player& player);
		bool Leave(Player& player);
		bool StartGame();

	private:
		Entity createEntity();
		bool deleteEntity(Entity& entity);

	private:
		entt::registry reg;

		Entity Deck;
		Entity Board;
		std::unordered_map<ID, Entity> Players;

		entt::scheduler<uint32_t> Process;
		RoomEventProcedure EventProc;
	};

	

}

