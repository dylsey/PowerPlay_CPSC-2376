
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

struct Object
{
	std::string name{};
	double strength{ 0 };
	double health{ 0 };
	int id{};
};
//giving global access without using header or class files
std::random_device seed;
std::default_random_engine engine(seed());
Object player;
Object monster;

std::vector<Object> monsters;

void createPlayer();
void displayMonsters();
void loadMonsters();
void displayBattle();
double attack(const Object& attacker);
double defend(Object& defender, int damage);
double heal(Object& healer);
void monsterAttack();
void playerAttack();
bool allMonstersDead();;

int main()
{
	displayBattle();
}

void createPlayer()
{
	std::normal_distribution<double> healthDist(30.0, 5.0);
	std::normal_distribution<double> strDist(5.0, 1.0);
	player.name = "Trogdor";
	do
	{
		player.strength = round(strDist(engine));
	}
	while (player.strength < 1.0);

	do
	{
		player.health = round(healthDist(engine));
	}
	while (player.health < 1.0);
}

void displayMonsters()
{
	std::cout << "Monsters: " << std::endl;
	int monsterChoice{ 1 };
	for (const auto& monster : monsters)
	{
		if (monster.health <= 0)
		{
			std::cout << "<DEAD> x_x" << std::endl;
		}
		else
		{
			std::cout << monsterChoice++ << ". " << monster.name << "\n"
				<< "health: " << monster.health << std::endl;
		}
	}
}

void loadMonsters()
{
	const std::string fileName("monsters.txt");
	std::fstream fin;
	fin.open(fileName);
	if (!fin.is_open())
	{
		std::cout << fileName << " did not open correctly" << std::endl;
	}

	int numOfMonstersInFile{};
	fin >> numOfMonstersInFile;

	//temporary vector to pull monsters from to put into the monster party vector
	std::vector<Object> allMonsters;
	for (int i{ 0 }; i < numOfMonstersInFile; i++)
	{
		Object monster;
		fin >> monster.name;
		fin >> monster.id;
		fin >> monster.strength;
		fin >> monster.health;
		allMonsters.push_back(monster);
	}

	std::uniform_int_distribution<int> monsterPartySizeDist(1, 3);
	int monsterPartySize = monsterPartySizeDist(engine);

	//shuffling the vector of allMonsters around to randomize the encounter
	std::shuffle(allMonsters.begin(), allMonsters.end(), engine);

	//pushes back the monsters after the shuffle has taken place
	for (int i{ 0 }; i < monsterPartySize; i++)
	{
		monsters.push_back(allMonsters[i]);
	}
}

// Damage dealt on attacks are based on a normal distribution with the mean being the object’s strength and a standard deviation of 2.
void displayBattle()
{
	createPlayer();
	loadMonsters();
	std::cout << "Welcome to the Haunted Forest " << std::endl;
	std::cout << "Be wary of Monsters!!!" << std::endl;
	std::cout << player.name << " the brave warrior enters the forest..." << std::endl;

	while (player.health > 0 && !allMonstersDead())
	{
		std::cout << player.name
			<< " health: " << player.health
			<< " strength: " << player.strength << std::endl;
		std::cout << std::endl;

		system("pause");
		system("CLS");
		//Player Action 
		std::cout << std::endl;

		std::cout << player.name << ", do you want to attack or heal? Enter 1 for attack and 2 for heal. " << std::endl;
		std::cout << std::endl;

		displayMonsters();

		int playerAction{};
		std::cin >> playerAction;
		system("CLS");

		if (playerAction == 1)
		{
			playerAttack();
			
		}
		if (playerAction == 2)
		{
			heal(player);
		}

		system("pause");
		system("CLS");

		monsterAttack();
	}

	if (player.health <= 0)
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (player.health <= 0 && allMonstersDead())
	{
		std::cout << "BUT" << std::endl;
	}
	if (allMonstersDead())
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");
}

double attack(const Object& attacker)
{
	std::normal_distribution<double> attackDist(attacker.strength, 2);
	double damage;
	do
	{
		damage = round(attackDist(engine));
	}
	while (damage < 1.0);

	return damage;
}

double defend(Object& defender, int damage)
{
	defender.health -= damage;
	std::cout << damage << " damage to " << defender.name << "!!!" << std::endl;
	if (defender.health < 0)
	{
		defender.health = 0;
	}
	return defender.health;
}


double heal(Object& healer)
{
	std::normal_distribution<double> healDist(healer.strength * 2, 3);
	double healAmount;
	do
	{
		healAmount = round(healDist(engine));
	}
	while (healAmount < 1.0);

	healer.health += healAmount;
	std::cout << healer.name << " heals for " << healAmount << " health!" << std::endl;
	return healer.health;
}

void monsterAttack()
{
	if (!allMonstersDead())
	{
		std::cout << "Monster's Turn!!! " << std::endl;
		//monster attack
		std::bernoulli_distribution willAttack(0.75);

		for (const auto& monster : monsters)
		{
			if (monster.health > 0)
			{
				if (willAttack(engine))
				{
					std::cout << monster.name << " attacks!" << std::endl;
					defend(player, attack(monster));
				}
				else
				{
					std::cout << monster.name << " attacks and misses! Wiff! " << std::endl;
				}
			}
		}
	}
}

void playerAttack()
{
	if (!allMonstersDead())
	{
		std::cout << "Choose a monster to attack:" << std::endl;
		displayMonsters();

		int playerAttackChoice;
		std::cin >> playerAttackChoice;
		while (playerAttackChoice < 1 || playerAttackChoice > monsters.size())
		{
			std::cout << "please choose a vaild number. " << std::endl;
			std::cin >> playerAttackChoice;
		}

		defend(monsters.at(playerAttackChoice - 1), attack(player));

		if (monsters.at(playerAttackChoice - 1).health <= 0)
		{
			std::cout << monsters.at(playerAttackChoice - 1).name << " has been kilt ded! x_x" << std::endl;
		}
		else
		{
			std::cout << monsters.at(playerAttackChoice - 1).name << " health: " << monsters.at(playerAttackChoice - 1).health << std::endl;
		}
	}
}

bool allMonstersDead()
{
	for (const auto& monster : monsters)
	{
		if (monster.health > 0)
		{
			return false;
		}
	}
	return true;
}