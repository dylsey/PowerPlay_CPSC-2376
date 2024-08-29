#include <iostream>
#include <string>
#include <vector>
#include <random>

struct Player
{
	std::string name{ "Trogdor" };
	int strength{ 0 };
	int health{ 0 };
};

struct Monster
{
	std::string monsterName{ "monster" };
	int monsterNumber{ 0 };
	int strength{ 0 };
	int health{ 0 };
};

//giving global access to engines, player, and monster vector
std::random_device seed;
std::default_random_engine engine(seed());
std::normal_distribution<double> healthDist(30.0, 5.0);
std::normal_distribution<double> strDist(5.0, 1.0);
std::uniform_int_distribution<int> monsterPartySize(1, 3);
std::bernoulli_distribution monsterAttackChance(0.75);
std::vector<Monster> monsters(monsterPartySize(engine));
Player playerOne;

void createPlayer();
void createMonsters();

int main()
{

	createPlayer();
	createMonsters();

	while (playerOne.health > 0)
	{
		//print player
		std::cout << playerOne.name << " health: " << playerOne.health << " strength: " << playerOne.strength << std::endl;
		std::cout << std::endl;
		//print monsters
		std::cout << "Monsters: " << std::endl;
		for (Monster monster : monsters)
		{
			std::cout << monster.monsterName << " health: " << monster.health << std::endl;
		}
		system("pause");
		system("CLS");
		//Player Action 
		std::cout << std::endl;
		std::cout << playerOne.name << ", do you want to attack or heal? Enter 1 for attack and 2 for heal. " << std::endl;
		int playerAction{};
		std::cin >> playerAction;

		//Attack Choice Tree
		if (playerAction == 1)
		{
			std::cout << "Choose a monster to attack:" << std::endl;
			for (int i = 0; i < monsters.size(); i++)
			{
				std::cout << monsters.at(i).monsterName << " health: " << monsters.at(i).health << std::endl;
			}
			int playerAttackChoice;
			std::cin >> playerAttackChoice;

			//will throw out of bounds exception error -- need to handle this error in final program 
			switch (playerAttackChoice)
			{

			case 1:
			{
				std::cout << "monster hit for: " << playerOne.strength << " damage" << std::endl;
				monsters.at(0).health = monsters.at(0).health - playerOne.strength;
				std::cout << monsters.at(0).monsterName << " health: " << monsters.at(0).health << std::endl;
				break;
			}
			case 2:
			{
				std::cout << "monster hit for: " << playerOne.strength << " damage" << std::endl;
				monsters.at(1).health = monsters.at(1).health - playerOne.strength;
				std::cout << monsters.at(1).monsterName << " health: " << monsters.at(1).health << std::endl;
				break;
			}
			case 3:
			{
				std::cout << "monster hit for: " << playerOne.strength << " damage" << std::endl;
				monsters.at(2).health = monsters.at(2).health - playerOne.strength;
				std::cout << monsters.at(2).monsterName << " health: " << monsters.at(2).health << std::endl;
				break;
			}
			}
		}

		//healing action 
		if (playerAction == 2)
		{
			playerOne.health = playerOne.health + (playerOne.strength * 2);
			std::cout << "player health: " << playerOne.health << std::endl;
		}

		system("pause");
		system("CLS");

		std::cout << "Monster Turn!!! " << std::endl;
		//monster attack
		for (auto& monster : monsters)
		{
			//need to figure out dead monster not attacking
			if (monsterAttackChance(engine))
			{
				std::cout << monsterAttackChance(engine) << " engine " << std::endl;
				std::cout << monster.monsterName << " attacks for : " << monster.strength << std::endl;
				playerOne.health = playerOne.health - monster.strength;
				std::cout << playerOne.name << " health: " << playerOne.health << std::endl;
			}
			else
			{
				std::cout << "monster attacks and misses" << std::endl;
			}
		}


	}

}

void createPlayer()
{
	//Player Str
	playerOne.strength = strDist(engine);
	//error handling to make sure player strength > 1
	if (playerOne.strength < 1)
	{
		playerOne.strength = strDist(engine);
	}
	//std::cout << "strength: " << playerOne.strength << std::endl;

	//Player Health
	playerOne.health = healthDist(engine);
	//error handling to ensure health > 1
	if (playerOne.health < 1)
	{
		playerOne.health = healthDist(engine);
	}
	//std::cout << "health: " << playerOne.health << std::endl;
}

void createMonsters()
{
	for (int i = 0; i < monsters.size(); i++)
	{
		monsters.at(i).monsterNumber = i + 1;
		char numberChar = '0' + monsters.at(i).monsterNumber;
		monsters.at(i).monsterName = monsters.at(i).monsterName + " " + numberChar;

		monsters.at(i).health = healthDist(engine);
		monsters.at(i).strength = strDist(engine);

		//std::cout << monsters.at(i).monsterName << " " << 
		// "health: " << monsters.at(i).health << " " <<
		// "strength: " << monsters.at(i).strength << std::endl;
	}
}