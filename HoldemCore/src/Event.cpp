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
			return OnGameAction(event);
			break;
		}
		return false;
	}

	std::any RoomEventProcedure::OnReqeust(Event& event)
	{
		auto RequestType = static_cast<HodlemRequest>(event.Spec);
		switch (RequestType)
		{
		case HodlemRequest::PossibleAction:
			return bettingState.GetPossibleAction();
		case HodlemRequest::ResetBettingState:
			return bettingState.ResetTurn();
		case HodlemRequest::CheckBettingComplete:
			return bettingState.BettingComplete();
		case HodlemRequest::CheckGameComplete:
			return bettingState.GameComplete();
		case HodlemRequest::JudgeWinner:
			return bettingState.JudgeWinner(room);
		case HodlemRequest::ResetGame:
			return bettingState.ResetGame();
		}
		return -1;
	}

	bool RoomEventProcedure::OnGameAction(Event & event)
	{
		auto Action = static_cast<HodlemAction>(event.Spec);
		//ConsoleRenderer::Draw("OnEvent! GameAction : " + ToString(Action));

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
		auto& playerChip = room->reg.get<Chip>(From);
		auto& boardChip = room->Board.GetComponent<Chip>();

		if (!playerChip.Spend(100))
		{
			return false;
		}
		bettingState.LastAction = HodlemAction::BBing;
		bettingState.LastRaise = 100;
		bettingState.bettingAmount[From] = 100;

		boardChip.Get(100);
		return true;
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
		auto& playerChip = room->reg.get<Chip>(From);
		auto& boardChip = room->Board.GetComponent<Chip>();

		int pay = 0;
		auto bettingAmountIt = bettingState.bettingAmount.find(From);
		if (bettingAmountIt == bettingState.bettingAmount.end())
		{
			pay = bettingState.LastRaise + 1000;
		}
		else
		{
			auto bettingAmount = bettingAmountIt->second;
			pay = bettingState.LastRaise - bettingAmount + 1000;
		}

		if (!playerChip.Spend(pay))
		{
			return false;
		}
		
		bettingState.LastRaise += 1000;
		bettingState.LastAction = HodlemAction::Raise;
		bettingState.bettingAmount[From] = bettingState.LastRaise;
		bettingState.CallCount = 0;

		boardChip.Get(pay);

		return true;
	}

	bool RoomEventProcedure::OnAllin(entt::entity From)
	{
		auto& playerChip = room->reg.get<Chip>(From);
		auto& boardChip = room->Board.GetComponent<Chip>();

		bettingState.AllinFlag = true;
		bettingState.LastAction = HodlemAction::Allin;
		bettingState.CallCount = 0;

		bettingState.bettingAmount[From] = playerChip.Count;

		boardChip.Get(playerChip.Count);
		playerChip.Spend(playerChip.Count);

		return true;
	}

	bool RoomEventProcedure::OnCall(entt::entity From)
	{
		auto& playerChip = room->reg.get<Chip>(From);
		auto& boardChip = room->Board.GetComponent<Chip>();

		int pay = 0;
		auto bettingAmountIt = bettingState.bettingAmount.find(From);
		if (bettingAmountIt == bettingState.bettingAmount.end())
		{
			pay = bettingState.LastRaise;
		}
		else
		{
			auto bettingAmount = bettingAmountIt->second;
			pay = bettingState.LastRaise - bettingAmount;
		}

		if (!playerChip.Spend(pay))
		{
			return false;
		}

		bettingState.CallCount += 1;
		bettingState.bettingAmount[From] = bettingState.LastRaise;
		boardChip.Get(pay);

		return true;
	}

	bool RoomEventProcedure::OnDie(entt::entity From)
	{
		bettingState.die.emplace_back(From);
		auto& hand = room->reg.get<Hand<2>>(From);
		hand.Vacate();

		return true;
	}

	bool BettingState::BettingComplete()
	{
		if (die.size() == PlayerCount - 1)
			return true;

		if (CallCount + die.size() == PlayerCount - 1)
			return true;

		return false;
	}

	bool BettingState::GameComplete()
	{
		if (die.size() == PlayerCount - 1)
			return true;

		return false;
	}

	std::vector<uint32_t> BettingState::GetPossibleAction()
	{
		std::vector<uint32_t> ret;
		ret.reserve(static_cast<size_t>(HodlemAction::None));

		if (LastAction == HodlemAction::None)
		{
			ret.emplace_back(static_cast<uint32_t>(HodlemAction::BBing));
			ret.emplace_back(static_cast<uint32_t>(HodlemAction::Check));
		}
		else
		{
			ret.emplace_back(static_cast<uint32_t>(HodlemAction::Call));
		}
		if (!AllinFlag)
		{
			ret.emplace_back(static_cast<uint32_t>(HodlemAction::Raise));
			ret.emplace_back(static_cast<uint32_t>(HodlemAction::Allin));
		}
		ret.emplace_back(static_cast<uint32_t>(HodlemAction::Die));

		return ret;
	}

	bool BettingState::ResetTurn()
	{
		bettingAmount.clear();

		LastRaise = 0;
		CallCount = 0;

		LastAction = HodlemAction::None;

		return true;
	}

	bool BettingState::ResetGame()
	{
		ResetTurn();

		die.clear();
		AllinFlag = false;
		PhaseCount = 0;

		return true;
	}

	namespace Ranks
	{
		enum : uint32_t
		{
			HighCard,
			OnePair,
			Twopair,
			ThreeKind,
			Straight,
			Flush,
			FullHouse,
			FourCard,
			StraightFlush,
			RoyalStrateFlush
		};

		std::string ToString(std::pair<uint32_t, uint32_t>& result)
		{
			std::string ret;
			if (result.first + result.second == 0)
			{
				return ret += "Die";
			}
			switch (result.first)
			{
			case HighCard:
				ret += "HighCard";
				break;
			case OnePair:
				ret += "OnePair";
				break;
			case Twopair:
				ret += "Twopair";
				break;
			case ThreeKind:
				ret += "ThreeKind";
				break;
			case Straight:
				ret += "Straight";
				break;
			case Flush:
				ret += "Flush";
				break;
			case FullHouse:
				ret += "FullHouse";
				break;
			case FourCard:
				ret += "FourCard";
				break;
			case StraightFlush:
				ret += "StraightFlush";
				break;
			case RoyalStrateFlush:
				ret += "RoyalStrateFlush";
				break;
			}

			if (result.first == FullHouse)
			{
				ret += " " + std::to_string(result.second / 100 + 1) + "Top";
			}
			else
			{
				ret += " " + std::to_string(result.second + 1) + "Top";
			}
			return ret;
		}

		std::pair<uint32_t, uint32_t> CheckCombo(const std::vector<Card>& cards)
		{
			uint32_t numberBoard[13]{0};
			uint32_t shapeBoard[4]{0};
			for (int i = 0; i < 7; ++i)
			{
				if (cards[i].PureNo == 52)
				{
					continue;
				}
				numberBoard[static_cast<uint32_t>(cards[i].Spec.Number)] += 1;
				shapeBoard[static_cast<uint32_t>(cards[i].Spec.Shape)] += 1;
			}

			int pairCount = 0;
			int treepleCount = 0;
			int fourCount = 0;
			int flushCount = 0;
			int straigtCount = 0;

			int pairMax = 0;
			int treepleMax = 0;
			int straigtMax = 0;
			int fourCardMax = 0;
			int topMax = 0;

			for (int i = 0; i < 4; ++i)
			{
				if (shapeBoard[i] == 5)
				{
					flushCount += 1;
				}
			}

			for (int i = 0; i < 13; ++i)
			{
				if (numberBoard[i])
				{
					topMax = i;
				}
				if (numberBoard[i] == 2)
				{
					pairCount += 1;
					pairMax = i;
				}
				if (numberBoard[i] == 3)
				{
					treepleCount += 1;
					treepleMax = i;
				}
				if (numberBoard[i] == 4)
				{
					fourCount += 1;
					fourCardMax = i;
				}

				if (straigtCount != 5)
				{
					if (numberBoard[i])
					{
						straigtCount += 1;
						if (straigtCount == 5)
						{
							straigtMax = i;
						}
					}
					else
					{
						straigtCount = 0;
					}
				}
			}

			if (numberBoard[9] && numberBoard[10] && numberBoard[11] && numberBoard[12] && numberBoard[0])
			{
				straigtCount = 5;
				straigtMax = 13;
			}

			if (straigtCount == 5 && flushCount == 5)
			{
				if (straigtMax == 13)
				{
					return { RoyalStrateFlush, 0 };
				}
				return { StraightFlush , straigtMax };
			}

			if (fourCount == 4)
			{
				return { FourCard, fourCardMax };
			}

			if (treepleCount >= 3 && pairCount >= 1)
			{
				return { FullHouse, treepleMax * 100 + pairMax };
			}

			if (flushCount == 5)
			{
				int flushMax = 0;
				for (int i = 12; i != 0; --i)
				{
					if (numberBoard[i])
					{
						flushMax = i;
						break;
					}
				}
				return { Flush, flushMax };
			}

			if (straigtCount == 5)
			{
				return { Straight, straigtMax };
			}

			if (treepleCount == 1)
			{
				return { ThreeKind , treepleMax };
			}

			if (pairCount >= 2)
			{
				return { Twopair, pairMax };
			}

			if (pairCount == 1)
			{
				return { OnePair, pairMax };
			}

			return { HighCard, topMax };
		};
		

	}

	std::string BettingState::JudgeWinner(Room* room)
	{
		std::vector<Card> boardCards;
		boardCards.reserve(7);

		auto& boardHands = room->Board.GetComponent<Hand<5>>();

		for (int i = 0; i < 5; ++i)
		{
			boardCards.emplace_back(boardHands.Hands[i]);
		}

		std::vector<std::pair<std::string, std::pair<uint32_t, uint32_t>>> v;

		for (auto&[id, entity] : room->Players)
		{
			std::vector<Card> totalCards(boardCards);
			auto& playerhand = entity.GetComponent<Hand<2>>();

			if (playerhand.Hands[0].PureNo == 52)
			{
				v.push_back({ id, { 0, 0 } });
				ConsoleRenderer::Draw(id + " : Die ");
				continue;
			}

			for (int i = 0; i < 2; ++i)
			{
				totalCards.emplace_back(playerhand.Hands[i]);
			}
			auto& result = Ranks::CheckCombo(totalCards);
			ConsoleRenderer::Draw(id + " : " + Ranks::ToString(result));
			v.emplace_back(id, result);
		}

		std::sort(v.begin(), v.end(), [](auto& lhs, auto& rhs) {
			if (lhs.second.first == rhs.second.first)
			{
				return lhs.second.second > rhs.second.second;
			}

			return lhs.second.first > rhs.second.first;
		});

		return v.begin()->first;
	}

}
