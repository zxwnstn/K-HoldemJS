#pragma once

namespace Core {

	
	enum class EventType
	{
		GameAction, Request
	};

	enum class HodlemRequest : uint32_t
	{
		ResetBettingState, CheckBettingComplete, CheckGameComplete, PossibleAction
	};

	enum class HodlemAction : uint32_t
	{
		BBing, Check, Raise, Allin, Call, Die, None
	};

	inline std::string to_string(HodlemAction action)
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
		bool BettingComplete()
		{
			if (DieCount - 1 == PlayerCount)
				return true;

			if (CallCount - 1 == PlayerCount)
				return true;

			return false;
		}

		bool GameComplete()
		{
			if (DieCount - 1 == PlayerCount)
				return true;

			return false;
		}

		uint32_t GetTotal() const noexcept
		{
			return Total;
		}

		std::vector<uint32_t> GetPossibleAction()
		{
			std::vector<uint32_t> ret;
			ret.reserve(static_cast<size_t>(HodlemAction::None));

			if (LastAction == HodlemAction::None)
			{
				ret.emplace_back(static_cast<uint32_t>(HodlemAction::BBing));
				ret.emplace_back(static_cast<uint32_t>(HodlemAction::Check));
			}
			if(!AllinFlag)
			{
				ret.emplace_back(static_cast<uint32_t>(HodlemAction::Raise));
				ret.emplace_back(static_cast<uint32_t>(HodlemAction::Allin));
			}
			ret.emplace_back(static_cast<uint32_t>(HodlemAction::Call));
			ret.emplace_back(static_cast<uint32_t>(HodlemAction::Die));

			return ret;
		}

		void Reset()
		{
			bettingAmount.clear();

			LastRaise = 0;
			CallCount = 0;
			Total = 0;
			DieCount = 0;
			PhaseCount = 0;
			LastAction = HodlemAction::None;
			AllinFlag = false;
		}

		std::unordered_map<entt::entity, uint32_t> bettingAmount;

		HodlemAction LastAction = HodlemAction::None;
		uint32_t LastRaise = 0;
		uint32_t CallCount = 0;
		uint32_t PlayerCount;
		uint32_t DieCount = 0;
		uint32_t Total = 0;
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

		std::vector<uint32_t> PossibleAction(entt::entity handle);
		bool ResetBettingState();
		bool CheckBettingComplete();

		BettingState bettingState;
		Room* room;
	};
}