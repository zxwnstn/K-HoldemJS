#pragma once

#include "pch.h"

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

	template<typename T, typename... Args>
	T& AttachComponenet(Args&&... args)
	{
		Reg.emplace<T>(Handle/*, std::forward(args)...*/);
		return Reg.get<T>(Handle);
	}

	entt::registry& Reg;
	entt::entity Handle;
};