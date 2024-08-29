#include <iostream>
#include <string>
#include <vector>
#include <random>

struct Object
{
	std::string name{};
	int strength{ 0 };
	int health{ 0 };
};

//giving global access to engines, player, and monster vector
std::random_device seed;
std::default_random_engine engine(seed());
std::normal_distribution<double> healthDist(30, 5);
std::normal_distribution<double> strDist(5.0, 1.0);
std::uniform_int_distribution<int> monsterPartySize(1, 3);
std::bernoulli_distribution monsterAttackChance(0.75);
std::normal_distribution<double> monsterAttackDist(monster.strength, 2);
std::normal_distribution<double> playerAttackDist(monster.strength, 2);



Object player;
Object monster;
std::vector<Object> monsters(monsterPartySize(engine));

void createPlayer();
void createMonsters();
int monsterAttack();
int playerAttack();


int main()
{
	createPlayer();
	createMonsters();

	while (player.health > 0)
	{
		//print player
		std::cout << player.name << " health: " << player.health << " strength: " << player.strength << std::endl;
		std::cout << std::endl;
		//print monsters
		std::cout << "Monsters: " << std::endl;
		for (auto& monster : monsters)
		{
			std::cout << monster.name << " health: " << monster.health << std::endl;
		}
		system("pause");
		system("CLS");
		//Player Action 
		std::cout << std::endl;
		std::cout << player.name << ", do you want to attack or heal? Enter 1 for attack and 2 for heal. " << std::endl;
		int playerAction{};
		std::cin >> playerAction;

		//Attack Choice Tree
		if (playerAction == 1)
		{
			std::cout << "Choose a monster to attack:" << std::endl;
			for (auto& monster : monsters)
			{
				std::cout << monster.name << " health: " << monster.health << std::endl;
			}
			int playerAttackChoice;
			std::cin >> playerAttackChoice;

			//will throw out of bounds exception error -- need to handle this error in final program 
			switch (playerAttackChoice)
			{
			case 1:
			{
				std::cout << "monster hit for: " << player.strength << " damage" << std::endl;
				monsters.at(0).health = monsters.at(0).health - player.strength;
				std::cout << monsters.at(0).name << " health: " << monsters.at(0).health << std::endl;
				break;
			}
			case 2:
			{
				std::cout << "monster hit for: " << player.strength << " damage" << std::endl;
				monsters.at(1).health = monsters.at(1).health - player.strength;
				std::cout << monsters.at(1).name << " health: " << monsters.at(1).health << std::endl;
				break;
			}
			case 3:
			{
				std::cout << "monster hit for: " << player.strength << " damage" << std::endl;
				monsters.at(2).health = monsters.at(2).health - player.strength;
				std::cout << monsters.at(2).name << " health: " << monsters.at(2).health << std::endl;
				break;
			}
			}
		}
		//healing action 
		if (playerAction == 2)
		{
			player.health = player.health + (player.strength * 2);
			std::cout << "player health: " << player.health << std::endl;
		}

		system("pause");
		system("CLS");

		std::cout << "Monster's Turn!!! " << std::endl;
		//monster attack
		for (auto& monster : monsters)
		{
			//need to figure out dead monster not attacking
			if (monsterAttackChance(engine))
			{
				std::cout << monsterAttackChance(engine) << " engine " << std::endl;
				std::cout << monster.name << " attacks for : " << monsterAttack();
				std::cout << std::endl;
				player.health = player.health - monster.strength;
				std::cout << player.name << " health: " << player.health << std::endl;
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
	player.name = "Trogdor";
	player.strength = strDist(engine);
	//error handling to make sure player strength > 1
	if (player.strength < 1)
	{
		player.strength = strDist(engine);
	}
	//std::cout << "strength: " << player.strength << std::endl;

	//Player Health
	player.health = healthDist(engine);
	//error handling to ensure health > 1
	if (player.health < 1)
	{
		player.health = healthDist(engine);
	}
	//std::cout << "health: " << player.health << std::endl;
}

void createMonsters()
{
	int monsterNumber{ 1 };
	for (auto& monster : monsters)
	{
		monster.name = "Monster " + std::to_string(monsterNumber++);
		monster.health = healthDist(engine);
		if (monster.health < 1)
		{
			monster.health = healthDist(engine);
		}
		monster.strength = strDist(engine);
		if (monster.strength < 1)
		{
			monster.strength = strDist(engine);
		}
		std::cout << monster.name << " " <<
			"health: " << monster.health << " " <<
			"strength: " << monster.strength << std::endl;
	}
}

//Damage dealt on attacks are based on a normal distribution with the mean being the object’s strength and a standard deviation of 2.

int monsterAttack(monsterAttackDist(engine)
{

	std::cout << "monster attack amt: " << std::endl;
	return
}

int playerAttack()
{

}
