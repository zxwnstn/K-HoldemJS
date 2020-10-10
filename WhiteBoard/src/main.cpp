#include <entt.hpp>
#include <iostream>	

struct my_process : entt::process<my_process, std::uint32_t> {
	using delta_type = std::uint32_t;

	my_process(delta_type delay)
		: remaining{ delay }
	{}

	void update(delta_type delta, void *) {
		remaining -= std::min(remaining, delta);

		// ...

		std::cout << "processing... \n";
		if (!remaining) {
			std::cout << "end";
			succeed();
			//__debugbreak();
		}
	}
private:
	delta_type remaining;
};


class A
{
	class B
	{
		void update()
		{
			this.a = 3;
		}

	};

	int a;
	int b;
};

int main()
{
	
}