#include "pch.h"
#include "CppUnitTest.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct Object
{
	std::string name;
	int strength{ 0 };
	int health{ 0 };
};
bool monsterAttack(Object& player, const std::vector<Object>& monsters);

namespace PP3UnitTest
{
	TEST_CLASS(PP3UnitTest)
	{
	public:
		TEST_METHOD(TestMonsterAttack)
		{
			Object player{ "MrTester", 5, 20 };
			std::vector<Object> monsters{ {"monster1", 3, 5}, {"monster2", 5, 15} };
			
			Assert::IsTrue(player.health <= 20);
			Assert::IsTrue(monsters.at(0).health = 5);
			Assert::IsTrue(monsters.at(1).health = 15);
		}
	};
}

