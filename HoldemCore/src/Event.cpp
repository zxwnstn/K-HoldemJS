#include "pch.h"

#include "Event.h"
#include "Room.h"

namespace Core {

	RoomEventProcedure::RoomEventProcedure(Room * room)
		: room(room)
	{
		
	}

	void RoomEventProcedure::Init()
	{
		bettingState.PlayerCount = room->GetPlayerCount();
	}

	bool RoomEventProcedure::OnEvent(Event& event)
	{
		switch (event.Type)
		{
		case EventType::GameAction:
			OnGameAction(event);
			break;
		}
	}

	std::any RoomEventProcedure::OnReqeust(Event& event)
	{
		auto RequestType = static_cast<HodlemRequest>(event.Spec);
		switch (RequestType)
		{
		case HodlemRequest::PossibleAction:
			return PossibleAction(event.FromID);
		case HodlemRequest::ResetBettingState:
			return ResetBettingState();
		case HodlemRequest::CheckBettingComplete:
			return CheckBettingComplete();
		}
		return -1;
	}

	bool RoomEventProcedure::OnGameAction(Event & event)
	{
		auto Action = static_cast<HodlemAction>(event.Spec);
		ConsoleRenderer::Draw("OnEvent! GameAction : " + to_string(Action));

		switch (Action)
		{
		case Core::HodlemAction::BBing:
			return OnBBing(event.FromID);
		case Core::HodlemAction::Check:
			return OnCheck(event.FromID);
		case Core::HodlemAction::Raise:
			return OnRaise(event.FromID);
		case Core::HodlemAction::Allin:
			return OnAllin(event.FromID);
		case Core::HodlemAction::Call:
			return OnCall(event.FromID);
		case Core::HodlemAction::Die:
			return OnDie(event.FromID);
		}
		return false;
	}

	bool RoomEventProcedure::OnBBing(entt::entity From)
	{
		auto& chip = room->reg.get<Chip>(From);
		bettingState.LastAction = HodlemAction::BBing;
		bettingState.LastRaise = 100;
		bettingState.bettingAmount[From] = 100;

		return chip.Spend(100);
	}

	bool RoomEventProcedure::OnCheck(entt::entity From)
	{
		auto& chip = room->reg.get<Chip>(From);
		bettingState.LastAction = HodlemAction::Check;
		bettingState.bettingAmount[From] = 0;

		return chip.Spend(0);
	}

	bool RoomEventProcedure::OnRaise(entt::entity From)
	{
		auto& chip = room->reg.get<Chip>(From);
		bettingState.LastAction = HodlemAction::Raise;

		int Pay = 0;
		if (bettingState.bettingAmount.find(From) == bettingState.bettingAmount.end())
		{
			Pay = bettingState.LastRaise + 1000;
		}
		else
		{

		}
		

		bettingState.LastRaise = 
		bettingState.bettingAmount[From] = bettingState.LastRaise;


		return chip.Spend(Pay);
	}

	bool RoomEventProcedure::OnAllin(entt::entity From)
	{
		auto& chip = room->reg.get<Chip>(From);
		bettingState.AllinFlag = true;
		bettingState.LastAction = HodlemAction::Allin;
		return false;
	}

	bool RoomEventProcedure::OnCall(entt::entity From)
	{
		auto& chip = room->reg.get<Chip>(From);
		bettingState.CallCount += 1;
		return false;
	}

	bool RoomEventProcedure::OnDie(entt::entity From)
	{
		auto& chip = room->reg.get<Chip>(From);
		bettingState.DieCount += 1;
		return false;
	}

	


	std::vector<uint32_t> RoomEventProcedure::PossibleAction(entt::entity From)
	{
		return bettingState.GetPossibleAction();
	}

	bool RoomEventProcedure::ResetBettingState()
	{
		return bettingState.BettingComplete();
	}

	bool RoomEventProcedure::CheckBettingComplete()
	{
		return bettingState.GameComplete();
	}

}