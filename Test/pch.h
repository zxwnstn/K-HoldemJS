#pragma once

#include <gtest/gtest.h>
#include <entt.hpp>

#define WITH_MOCK 1

#if WITH_MOCK
	#define Obj(Class) Mock::Class
#else
	#define Obj(Class) Class
#endif
