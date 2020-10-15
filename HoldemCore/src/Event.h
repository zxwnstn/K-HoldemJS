#pragma once

#include <string>

namespace Core {

	
	enum class EventType
	{
		GameAction, Request
	};

	enum class HodlemRequest : uint32_t
	{
		ResetBettingState, CheckBettingComplete, CheckGameComplete, PossibleAction, JudgeWinner
	};

	enum class HodlemAction : uint32_t
	{
		BBing, Check, Raise, Allin, Call, Die, None
	};

	inline std::string ToString(HodlemAction action)
	{
		switch (action)
		{
		case Core::HodlemAction::BBing:
			return "BBing";
		case Core::HodlemAction::Check:
			return "Check";
		case Core::HodlemAction::Raise:
			return "Raise";
		case Core::HodlemAction::Allin:
			return "Allin";
		case Core::HodlemAction::Call:
			return "Call";
		case Core::HodlemAction::Die:
			return "Die";
		case Core::HodlemAction::None:
			return "None";
		}
		return "";
	}

	struct Event
	{
		EventType Type;
		uint32_t Spec;
		entt::entity FromID;
	};

	struct BettingState
	{
		bool BettingComplete();

		bool GameComplete();

		std::string JudgeWinner(class Room* room);
		std::vector<uint32_t> GetPossibleAction();
		bool ResetTurn();
		bool ResetGame();

		std::unordered_map<entt::entity, uint32_t> bettingAmount;
		std::vector<entt::entity> die;

		HodlemAction LastAction = HodlemAction::None;
		uint32_t LastRaise = 0;
		uint32_t CallCount = 0;
		uint32_t PlayerCount;
		uint32_t PhaseCount = 0;
		bool AllinFlag = false;
	};

	struct RoomEventProcedure
	{
		RoomEventProcedure(class Room* room);
		void Init();

		bool OnEvent(Event& event);
		std::any OnReqeust(Event& event);
		
		bool OnGameAction(Event& event);
		
		bool OnBBing(entt::entity From);
		bool OnCheck(entt::entity From);
		bool OnRaise(entt::entity From);
		bool OnAllin(entt::entity From);
		bool OnCall(entt::entity From);
		bool OnDie(entt::entity From);

		BettingState bettingState;
		Room* room;
	};
}