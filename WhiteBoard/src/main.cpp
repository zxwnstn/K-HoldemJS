#include <unordered_map>
#include <string>
#include <iostream>

enum class AA
{
	a, b, c, d, max
};

int main()
{
	int max = static_cast<int>(AA::max);

	AA b;
	for (int i = 0; i < max; ++i)
	{
		b = static_cast<AA>(i);
	}

}