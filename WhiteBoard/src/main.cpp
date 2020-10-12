//#include <unordered_map>
//#include <string>
//#include <iostream>
//#include "entt.hpp"
//
//
//struct someStruct
//{
//	int a = 3;
//};
//
//struct Fstruct
//{
//	int count = 0;
//};
//
//struct Manager
//{
//	void UpdateComponent()
//	{
//		std::cout << "update!";
//	}
//
//	template<typename T>
//	void update(T& comp)
//	{
//		comp.a = 3;
//		std::cout << "update";
//	}
//
//	template<typename T>
//	void operator()(T& comp)
//	{
//		std::cout << "update";
//	}
//
//};
//
//entt::registry reg;
//Manager manager;
//
//int main()
//{
//	auto entity = reg.create();
//	reg.emplace<someStruct>(entity);
//	reg.emplace<Fstruct>(entity);
//
//	//reg.on_update<someStruct>().connect<&Manager::UpdateComponent>(manager);
//
//	//reg.patch<someStruct>(entity, [](auto &pos) 
//	//{
//	//	pos.a += 3;
//	//	auto thisEntity = entt::to_entity(reg, pos);
//	//});
//
//	reg.patch<someStruct>(entity, manager);
//
//}

template<typename GameProcedure, typename EventProcessor>
struct Room
{
	Room()
		: proc(*this), eventHandle(*this)
	{
	}

	GameProcedure proc;
	EventProcessor eventHandle;
};

struct HoldemProcedure
{
	template<typename T, typename U>
	using RoomBase = Room<T, U>;
	using RoomType = RoomBase<HoldemProcedure, class HoldemEventProc>;


	HoldemProcedure(RoomType& thisRoom)
		: ThisRoom(thisRoom)
	{
	}

	int a;
	RoomType& ThisRoom;
};

struct HoldemEventProc
{
	template<typename T, typename U>
	using RoomBase = Room<T, U>;
	using RoomType = RoomBase<HoldemProcedure, HoldemEventProc>;

	HoldemEventProc(RoomType& thisRoom)
		: ThisRoom(thisRoom)
	{
	}

	int b;
	RoomType& ThisRoom;
};

int main()
{
	Room<HoldemProcedure, HoldemEventProc> room;

}