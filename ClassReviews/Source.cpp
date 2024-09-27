#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


int main()
{
	std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> vec2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	auto lambda{ [&](int num1, int num2) -> int
		{
			return num1 * num2;
		} };

	std::transform(vec.begin(), vec.end(), vec2.begin(), vec2.begin(), lambda);

	for (auto i : vec2)
	{
		std::cout << i << std::endl;
	}

	return 0;
}
