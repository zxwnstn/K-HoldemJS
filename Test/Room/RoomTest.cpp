#include "pch.h"

#include "Player/MockPlayer.h"
#include "MockRoom.h"

TEST(Room, Join)
{
	Obj(Room) room;

	EXPECT_TRUE(room.Join("zxwnstn"_hs));
	EXPECT_TRUE(room.Join("kiseop"_hs));

	EXPECT_FALSE(room.Join("kiseop"_hs));
}

TEST(RoomEvent, OnBetting)
{
	Obj(Room) room;

	EXPECT_TRUE(room.Join("zxwnstn"_hs));
	EXPECT_TRUE(room.Join("kiseop"_hs));

	

}

TEST(RoomEvent, OnReward)
{
	Obj(Room) room;
	Obj(Player) player1("kiseop");
	Obj(Player) player2("zxwnstn");



}
