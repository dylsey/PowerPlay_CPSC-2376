#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>

#include "Item.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"

std::vector<Monster> createMonsters(const Player& player);

void displayBattle(const Player& player, const std::vector<Monster>& monsters);
void bringOutYourDead(std::vector<Monster>& monsters);


int main()
{
	Player player;
	std::vector<Monster> monsters;
	while (!player.isDead())
	{
		player.levelUp();
		monsters = createMonsters(player);

		std::cout << monsters.size() << " monster(s) approaches!!" << std::endl;
		system("pause");
		system("cls");

		while (!player.isDead() && monsters.size() > 0)
		{

			displayBattle(player, monsters);

			player.update(player, monsters);

			bringOutYourDead(monsters);

			std::cout << std::endl;
			std::for_each(monsters.begin(), monsters.end(), [&](Monster& monster)
				{
					monster.update(player, monsters);
				});

			system("PAUSE");
			system("CLS");
		}
	}

	if (player.isDead())
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (player.isDead() && monsters.size() == 0)
	{
		std::cout << "BUT" << std::endl;
	}
	if (monsters.size() == 0)
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");

}



void displayBattle(const Player& player, const std::vector<Monster>& monsters)
{
	std::cout << player << std::endl;
	std::cout << std::endl << "  Monsters: " << std::endl;
	{
		int i{ 1 };
		std::for_each(monsters.begin(), monsters.end(), [&](const Monster& monster)
			{
				std::cout << "   " << i << ". " << monster << std::endl;

				i++;
			});
	}
}

std::vector<Monster> createMonsters(const Player& player)
{
	std::normal_distribution<double> randomNumMonsters((double)player.getLevel(), player.getLevel() / 2.0);
	std::vector<Monster> monsters(std::max(1, (int)randomNumMonsters(Object::engine)));
	std::generate(monsters.begin(), monsters.end(), [&]()
		{
			return Monster(player);
		});
	return monsters;
}

void bringOutYourDead(std::vector<Monster>& monsters)
{
	monsters.erase(
		std::remove_if(monsters.begin(), monsters.end(),
			[](Object& monster)
			{
				if (monster.isDead())
				{

					std::cout << monster << " has died!!!" << std::endl << std::endl;
					return true;
				}
				return false;
			}),
		monsters.end());

}