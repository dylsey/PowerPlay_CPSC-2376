#include "Monster.h"
#include <vector>
#include <algorithm>
#include <random>

std::random_device seed;
std::default_random_engine engine(seed());

Monster::Monster()
{
}


Monster::Monster(Object::Type type, int strength, int health, int level)
{
	this->type = type;
	this->strength = strength;
	this->health = health;
	this->level = level;
}

void Monster::monsterAttack(Object& player,  std::vector<Monster>& monsters)
{
	std::cout << std::endl;
	std::for_each(monsters.begin(), monsters.end(), [&](Object& monster)
		{
			std::bernoulli_distribution willAttack(.75);
			if (willAttack(engine))
			{
				std::cout << monster << " attacks!" << std::endl;
				monster.attack(player);

				defend(player, attack(monster));
			}
			else
			{
				std::cout << monster << " twiddles its thumbs" << std::endl;
			}
		});
}

std::vector<Monster> Monster::createMonsters(const Object& player)
{
	std::normal_distribution<double> randomNumMonsters((double)player.getLevel(), player.getLevel() / 2.0);
	std::vector<Monster> monsters(std::max(1, (int)randomNumMonsters(engine)));
	std::generate(monsters.begin(), monsters.end(), [&]()
		{
			//set level based on player level
			std::normal_distribution<double> monsterLevel((float)player.getLevel(), player.getLevel() / 4.0);
			int level{ std::max(1, (int)monsterLevel(engine)) };

			std::uniform_int_distribution<int> monsterType(1, (int)Object::Type::numTypes - 1);
			Object::Type name{ (Object::Type)monsterType(engine) };

			double strengthVariance{ 0.0 };
			double healthVariance{ 0.0 };
			switch (name)
			{
			case Object::Type::slime:
				strengthVariance = level * 1.5;
				healthVariance = level * 1.25;
				break;
			case Object::Type::orc:
				strengthVariance = level * 2.0;
				healthVariance = (long long)level * level * 1.25;
				break;
			case Object::Type::sprite:
				strengthVariance = level * 1.75;
				healthVariance = level;
				break;
			case Object::Type::dragon:
				strengthVariance = level * 6.0;
				healthVariance = (long long)level * level * 3.0;
				break;
			}
			std::normal_distribution<double> randomStrength(strengthVariance, level / 4.0);
			std::normal_distribution<double> randomHealth(healthVariance * 5, level / 2.0);

			Monster monster();

			monster.type = name;
					monster.strength = std::max(1, (int)randomStrength(engine)),
					std::max(1, (int)randomHealth(engine)),
					level,

			
			return monster;
		});
	return monsters;
}
