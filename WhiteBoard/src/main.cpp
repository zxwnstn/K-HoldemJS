////#include <unordered_map>
////#include <string>
////#include <iostream>
////#include "entt.hpp"
////
////
////struct someStruct
////{
////	int a = 3;
////};
////
////struct Fstruct
////{
////	int count = 0;
////};
////
////struct Manager
////{
////	void UpdateComponent()
////	{
////		std::cout << "update!";
////	}
////
////	template<typename T>
////	void update(T& comp)
////	{
////		comp.a = 3;
////		std::cout << "update";
////	}
////
////	template<typename T>
////	void operator()(T& comp)
////	{
////		std::cout << "update";
////	}
////
////};
////
////entt::registry reg;
////Manager manager;
////
////int main()
////{
////	auto entity = reg.create();
////	reg.emplace<someStruct>(entity);
////	reg.emplace<Fstruct>(entity);
////
////	//reg.on_update<someStruct>().connect<&Manager::UpdateComponent>(manager);
////
////	//reg.patch<someStruct>(entity, [](auto &pos) 
////	//{
////	//	pos.a += 3;
////	//	auto thisEntity = entt::to_entity(reg, pos);
////	//});
////
////	reg.patch<someStruct>(entity, manager);
////
////}
//
//#include <entt.hpp>
//#include <iostream>
//struct Player { 
//	int p; 
//	void some()
//	{
//		int k;
//		auto func = [this]() 
//		{ 
//			std::cout << p << std::endl; 
//		};
//	}
//
//};
//struct Entity { int e; };
//
//
//template<typename GameProcedure, typename EventProcessor, typename... BasicComponents>
//struct RoomBase
//{
//	RoomBase()
//		: proc(*this), eventHandle(*this)
//	{
//	}
//
//	bool Join(const Player& player)
//	{
//	}
//
//	bool Leave(Player& player)
//	{
//
//	}
//	bool StartGame()
//	{
//		GameProc.attach<GameProcedure>(*this);
//		GameProc.update(1u);
//		return true;
//	}
//
//protected:
//	Entity createEntity() {}
//	bool deleteEntity(Entity& entity) {}
//
//	entt::registry Reg;
//	entt::scheduler<uint32_t> GameProc;
//	EventProcessor EventProc;
//};
//
//struct ProcedureBase
//{
//	template<typename GameProcedure, typename EventProcessor>
//	using RoomType = RoomBase<GameProcedure, EventProcessor>;
//
//	template<typename GameProcedure, typename EventProcessor>
//	ProcedureBase(RoomBase<GameProcedure, EventProcessor>& thisRoom)
//		: ThisRoom(thisRoom)
//	{
//	}
//
//	int a;
//	RoomType& room;
//};
//
//struct EventProcBase
//{
//	template<typename T, typename U>
//	HoldemEventProc(RoomType& thisRoom)
//		: ThisRoom(thisRoom)
//	{
//	}
//
//	int b;
//	RoomType& ThisRoom;
//};
//
//struct HoldemProcedure : ProcedureBase
//{
//
//};
//
//struct HoldemEventProc : EventProcBase
//{
//
//};
//
//int main()
//{
//	RoomBase<HoldemProcedure, HoldemEventProc> HoldemRoom;
//}

#include <unordered_map>
#include <functional>
#include <iostream>
int f(int) { return 0; }
int g(int) { return 1; }

void s(int a, int b, int c)
{
	std::cout << a << b << c;
}
// ...


struct ss
{
	ss(int a)
		: a(a)
	{}
	int a;
};
int main()
{
	std::unordered_map<std::string, ss> map;

	//auto& k = map["zxwnstn"];
	
}


