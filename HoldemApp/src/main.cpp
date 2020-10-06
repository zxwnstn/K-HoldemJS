#include <iostream>
#include <entt.hpp>
using namespace std;

int main()
{

	entt::registry reg;
	auto entity = reg.create();

	while(1)
	{
		std::cout << 1;
	}
	return 0;
}