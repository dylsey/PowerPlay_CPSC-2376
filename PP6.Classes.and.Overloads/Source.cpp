#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Item.h"
#include "Player.h"
#include "Monster.h"



std::vector<Object> createMonsters(const Object& player);
void monsterAttack(Object& player, const std::vector<Object>& monsters);
void bringOutYourDead(std::vector<Object>& monsters);



void displayBattle(const Object& player, const std::vector<Object>& monsters);


std::random_device seed;
std::default_random_engine engine(seed());

int main()
{
	Object player;
	
	{ Object::Type::player, 0,1,0, {} };
	std::vector<Object> monsters;
	while (player.health > 0)
	{
		levelUp(player);
		monsters = createMonsters(player);

		std::cout << monsters.size() << " monster(s) approaches!!" << std::endl;
		system("pause");
		system("cls");

		while (player.health > 0 && monsters.size() > 0)
		{

			displayBattle(player, monsters);

			std::cout << "What do you do? (a)ttack (h)eal ";
			char command{ 'x' };
			std::cin >> command;
			switch (command)
			{
			case 'a':
			{
				playerAttack(player, monsters);
				break;
			}
			case 'h':
			{
				player.heal(player);
				break;
			}
			default:
			{
				std::cout << "please enter a or h" << std::endl;
				break;
			}
			}

			bringOutYourDead(monsters);

			monsterAttack(player, monsters);

			system("PAUSE");
			system("CLS");
		}
	}

	if (player.health <= 0)
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (player.health <= 0 && monsters.size() == 0)
	{
		std::cout << "BUT" << std::endl;
	}
	if (monsters.size() == 0)
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");

}



void displayBattle(const Object& player, const std::vector<Object>& monsters)
{
	player.printName();

	printName(player.getType);
	std::cout << " h:" << player.health << std::endl;
	std::for_each(player.inventory.begin(), player.inventory.end(), [](std::pair<Item::Type, Item> item)
		{
			std::cout << "  ";
			printItem(item.second);
			std::cout << std::endl;
		});
	std::cout << std::endl << "  Monsters: " << std::endl;
	{
		int i{ 1 };
		std::for_each(monsters.begin(), monsters.end(), [&](const Object& monster)
			{
				std::cout << "   " << i << ". ";
				printName(monster);
				std::cout << " h:" << monster.health << std::endl;
				i++;
			});
	}
}

std::vector<Object> createMonsters(const Object& player)
{
	std::normal_distribution<double> randomNumMonsters((double)player.level, player.level / 2.0);
	std::vector<Object> monsters(std::max(1, (int)randomNumMonsters(engine)));
	std::generate(monsters.begin(), monsters.end(), [&]()
		{
			//set level based on player level
			std::normal_distribution<double> monsterLevel((float)player.level, player.level / 4.0);
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

			Object monster(
				{
					name,
					std::max(1, (int)randomStrength(engine)),
					std::max(1, (int)randomHealth(engine)),
					level,
					{}
				});
			return monster;
		});
	return monsters;
}

void monsterAttack(Object& player, const std::vector<Object>& monsters)
{

	std::cout << std::endl;
	std::for_each(monsters.begin(), monsters.end(), [&](const Object& monster)
		{
			std::bernoulli_distribution willAttack(.75);
			if (willAttack(engine))
			{
				printName(monster);
				std::cout << " attacks!" << std::endl;
				defend(player, attack(monster));
			}
			else
			{
				printName(monster);
				std::cout << " twiddles its thumbs" << std::endl;
			}
		});
}

void playerAttack(const Object& player, std::vector<Object>& monsters)
{
	std::cout << "Which Monster: ";
	int monsterNum{ 0 };
	std::cin >> monsterNum;
	if (monsterNum > 0 && monsterNum <= monsters.size())
	{
		defend(monsters[monsterNum - 1], attack(player));
	}
}

void levelUp(Object& player)
{
	player.level++;
	std::normal_distribution<double> randomHealth(20.0 + player.level * 5, 5.0);
	player.health += std::max(1, (int)randomHealth(engine));

	std::normal_distribution<double> randomStrength(3.0 + player.level, 1.0);
	player.strength += std::max(1, (int)randomStrength(engine));

	//grab new item.
	std::uniform_int_distribution<int> randomItem(0, (int)Item::Type::numTypes - 1);
	std::normal_distribution<double> randomBonus((double)player.level, (double)player.level / 2);
	Item found{ (Item::Type)randomItem(engine), std::max(1, (int)randomBonus(engine)) };

	std::cout << "You found a ";
	printItem(found);
	std::cout << "!!!!" << std::endl;
	if (
		auto haveOne{ player.inventory.find(found.clasification) };
		haveOne == player.inventory.end()
		|| player.inventory[found.clasification].bonusValue < found.bonusValue
		)
	{
		std::cout << "You keep the shiny new toy!" << std::endl;
		player.inventory[found.clasification] = found;
	}
	else
	{
		std::cout << "You toss aside the ugly old thing!" << std::endl;
	}
}


void bringOutYourDead(std::vector<Object>& monsters)
{
	monsters.erase(
		std::remove_if(monsters.begin(), monsters.end(),
			[](Object& monster)
			{
				if (monster.health <= 0)
				{
					printName(monster);
					std::cout << " has died!!!" << std::endl << std::endl;
					return true;
				}
				return false;
			}),
		monsters.end());

}


