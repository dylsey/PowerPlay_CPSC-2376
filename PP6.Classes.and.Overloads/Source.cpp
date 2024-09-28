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



void monsterAttack(Object& player, const std::vector<Object>& monsters);
void bringOutYourDead(std::vector<Object>& monsters);

void displayBattle(const Object& player, const std::vector<Object>& monsters);

std::random_device seed;
std::default_random_engine engine(seed());

int main()
{
	Object player;
	
	//{ Object::Type::player, 0,1,0, {} };
	std::vector<Object> monsters;
	while (player.getHealth() > 0)
	{
		levelUp(player);
		monsters = createMonsters(player);

		std::cout << monsters.size() << " monster(s) approaches!!" << std::endl;
		system("pause");
		system("cls");

		while (player.getHealth() > 0 && monsters.size() > 0)
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

	if (player.getHealth() <= 0)
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (player.getHealth() <= 0 && monsters.size() == 0)
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
	//player.printName();
	player.getType(); 
	//printName(player.getType);
	std::cout << " h:" << player.getHealth() << std::endl;


	std::for_each(player.inventory.begin(), player.inventory.end(), [](std::pair<Item::Type, Item> item)
		{
			std::cout << item.second <<  "  " << std::endl;
			//printItem(item.second);
			std::cout << std::endl;
		});

	std::cout << std::endl << "  Monsters: " << std::endl;
	{
		int i{ 1 };
		std::for_each(monsters.begin(), monsters.end(), [&](const Object& monster)
			{
				std::cout << "   " << i << ". " << monster;
				//printName(monster);
				std::cout << " h:" << monster.getHealth() << std::endl;
				i++;
			});
	}
}

std::vector<Object> createMonsters(const Object& player)
{
	
}

void monsterAttack(Object& player, const std::vector<Object>& monsters)
{

	std::cout << std::endl;
	std::for_each(monsters.begin(), monsters.end(), [&](const Object& monster)
		{
			std::bernoulli_distribution willAttack(.75);
			if (willAttack(engine))
			{
				std::cout << monster << " attacks!" << std::endl;
				defend(player, attack(monster));
			}
			else
			{
				
				std::cout << monster << " twiddles its thumbs" << std::endl;
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
	
}


void bringOutYourDead(std::vector<Object>& monsters)
{
	monsters.erase(
		std::remove_if(monsters.begin(), monsters.end(),
			[](Object& monster)
			{
				if (monster.getHealth() <= 0)
				{
					
					std::cout << monster << " has died!!!" << std::endl << std::endl;
					return true;
				}
				return false;
			}),
		monsters.end());

}


