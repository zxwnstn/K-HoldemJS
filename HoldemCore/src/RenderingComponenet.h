#pragma once

#include <sstream>
#include <string>

namespace Core {

	struct ConsoleSprite
	{
		ConsoleSprite()
		{
		}

		void Clear()
		{
			stream.str("");
		}

		template<typename Target>
		[[maybe_unused]]
		typename std::enable_if_t <
			std::is_same_v<void,
			std::void_t<decltype(std::declval<std::stringstream>() << std::declval<Target>())>>,
			ConsoleSprite&
		>
			operator << (const Target& target)
		{
			stream << target;
			return *this;
		}

		template<typename RenderTarget>
		[[maybe_unused]]
		typename std::void_t<decltype(std::declval<RenderTarget>().DrawContext())>
			operator()(RenderTarget& target)
		{
			target.DrawContext(*this);
		}

		std::stringstream stream;

	#if _DEBUG
		template<typename RenderTarget>
		bool operator()(RenderTarget& target)
		{
			std::cout << "Can't be drawn by Console";
			return false;
		}
	#endif
	};

}