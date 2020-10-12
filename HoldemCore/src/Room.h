#include "Entity.h"

#include "Player.h"
#include "SubComponent.h"

namespace Core {

	struct Event
	{

	};

	struct Room
	{
		using Host = entt::tag<"Host"_hs>;

	private:
		struct GameProcess : entt::process<GameProcess, std::uint32_t>
		{
		public:
			enum class Phase : unsigned int
			{
				PreFlop, Flop, Turn, River, Clear, End
			};

			friend Phase& operator++(Phase& phase)
			{
				if (phase == Phase::End)
					return phase;
				auto ToInt = static_cast<unsigned int>(phase);
				return phase = static_cast<Phase>(++ToInt);
			}

		private:
			void progPreFlop();
			void progFlop();
			void progTurn();
			void progRiver();
			void progClear();
			void progBetting();

			template<typename _Hand>
			[[maybe_unused]]
			typename std::void_t<decltype(std::declval<_Hand>().TakeCard(Card()))>
				FillCard(_Hand& Reciever, uint32_t count = 1)
			{
				auto& deck = ThisRoom.Deck.GetComponent<Hand<52>>();
				while (count--)
				{
					Reciever.TakeCard(deck.BringCard());
				}
			}

		private:
			void RenderDeckHand();
			void RenderPlayerHand();
			void RenderBoardHand();

		public:
			GameProcess(Room& thisRoom);
			Phase UpdateState();
			void update(delta_type delta, void* anotherData);
			void PauseProc();

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

			void ComponentUpdate()
			{

			}

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

