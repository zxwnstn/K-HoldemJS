#include "pch.h"

#include "MockBoard.h"

TEST(Board, Init)
{
	Obj(Board) board;

	EXPECT_EQ(board.AccumChips.Count, 0);
	EXPECT_EQ(board.Cards[0].Spec.Number, Obj(CardNumber)::None);
	EXPECT_EQ(board.Cards[0].Spec.Shape, Obj(CardShape)::None);

	EXPECT_EQ(board.Cards[4].Spec.Number, Obj(CardNumber)::None);
	EXPECT_EQ(board.Cards[4].Spec.Shape, Obj(CardShape)::None);
}