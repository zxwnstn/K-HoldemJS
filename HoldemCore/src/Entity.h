#pragma once

#include "entt.hpp"
#include <utility>

namespace Core {

	struct Entity
	{
		Entity(entt::registry& reg)
			: Reg(reg)
		{
			Handle = Reg.create();
		}

		template<typename T>
		T& GetComponent()
		{
			return Reg.get<T>(Handle);
		}

		template<typename T, typename... Args>
		void AttachComponenet(Args&&... args)
		{
			Reg.emplace<T>(Handle, std::forward<Args>(args)...);
		}

		entt::registry& Reg;
		entt::entity Handle;
	};

}
