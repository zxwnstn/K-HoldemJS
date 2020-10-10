#include "pch.h"

#include "MockPlayer.h"

TEST(PlayerAction, Bet)
{
	Obj(Player) player("Hong");

	EXPECT_TRUE(player.Bet(100));
	EXPECT_EQ(player.Chips.Count, 200);
	EXPECT_TRUE(player.Bet(200));
	EXPECT_EQ(player.Chips.Count, 0);

	EXPECT_FALSE(player.Bet(200));
}

TEST(PlayerAction, Raise)
{
	Obj(Player) player("Hong");
	
	EXPECT_TRUE(player.Rasie(100));
	EXPECT_EQ(player.Chips.Count, 200);
	EXPECT_TRUE(player.Rasie(200));
	EXPECT_EQ(player.Chips.Count, 0);

	EXPECT_FALSE(player.Rasie(200));
}

TEST(PlayerAction, Fold)
{
	Obj(Player) player("Hong");
	player.Fold();

	EXPECT_EQ(player.Hands.size(), 0);
}

TEST(PlayerAction, Check)
{
	Obj(Player) player("Hong");

	player.Check();
	EXPECT_EQ(player.Chips.Count, 300);
}