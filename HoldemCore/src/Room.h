#pragma once 

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

			std::string ToString(Phase& phase)
			{
				switch (phase)
				{
				case Phase::PreFlop: return "PreFlop";
				case Phase::Flop: return "Flop";
				case Phase::Turn: return "Turn";
				case Phase::River: return "River";
				case Phase::Clear: return "Clear";
				}
				return "";
			}

		private:
			void progPhase();
			void progClear();
			void progBetting();

			template<typename _Hand>
			[[maybe_unused]]
			typename std::void_t<decltype(std::declval<_Hand>().TakeCard(std::declval<Card>()))>
				FillCard(_Hand& Reciever, uint32_t count = 1)
			{
				auto& deck = ThisRoom.Deck.GetComponent<Hand<52>>();
				while (count--)
				{
					Reciever.TakeCard(deck.BringCard());
				}
			}

		private:
			void RenderDeck();
			void RenderPlayer(ID id);
			void RenderBoard();

		public:
			GameProcess(Room& thisRoom);
			Phase UpdateState();
			void update(delta_type delta, void* anotherData);
			void PauseProc();
			
		private:
			bool BettingDone;
			std::unordered_map<ID, Entity>::iterator PlayerIterator;
			Phase CurPhase;
			Room& ThisRoom;
		};

	public:
		Room();

		bool Join(const Player& player);
		bool Leave(Player& player);
		bool StartGame();
		inline size_t GetPlayerCount() const { return Players.size(); }

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

		friend class RoomEventProcedure;
		friend class BettingState;
	};



}

