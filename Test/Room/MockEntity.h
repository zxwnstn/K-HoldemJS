#include <entt.hpp>

namespace Mock {

	struct Entity 
	{
		Entity(entt::registry& reg)
			: Reg(reg)
		{
			Handle = Reg.create();
		}

		template<typename T>
		T& GetComponent(entt::entity entity)
		{
			return Reg.get<T>(entity);
		}

		entt::registry& Reg;
		entt::entity Handle;
	};

}