#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

struct Object
{
	std::string name;
	int strength{ 0 };
	int health{ 0 };
};

std::vector<Object> loadMonsters(const std::string& fileName);
void displayBattle(const Object& player, const std::vector<Object>& monsters);
bool monsterAttack(Object& player, const std::vector<Object>& monsters);
void playerAttack(const Object& player, std::vector<Object>& monsters);
int attack(const Object& object);
void defend(Object& object, int damage);
void heal(Object& object);

std::random_device seed;
std::default_random_engine engine(seed());

int main()
{

	std::normal_distribution<double> randomHealth(30.0, 5.0);
	std::normal_distribution<double> randomStrength(8.0, 1.0);

	Object player
	{
		"Mr. Orme",
		std::max(1, (int)randomStrength(engine)),
		std::max(1, (int)randomHealth(engine))
	};

	std::vector<Object> monsters{ loadMonsters("monsters.txt") };


	std::cout << monsters.size() << " monster(s) approaches!!" << std::endl;
	//There is an assumption of at least one monster.
	do
	{
		system("PAUSE");
		system("CLS");

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
			heal(player);
			break;
		default:
			std::cout << "please enter a or h" << std::endl;
			break;
		}


	}
	while (player.health > 0 && !monsterAttack(player, monsters));

	if (player.health <= 0)
	{
		std::cout << "You Have Died" << std::endl;
	}
	else
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");

}

std::vector<Object> loadMonsters(const std::string& fileName)
{
	std::fstream fin;
	fin.open(fileName);
	std::vector<Object> monsters;
	if (fin.is_open())
	{
		int numMonsters;
		fin >> numMonsters;
		for (int i{ 0 }; i < numMonsters; i++)
		{
			std::string name;
			int strength;
			int health;
			fin >> name >> strength >> health;
			monsters.push_back({ name, strength, health });
		}
	}
	fin.close();
	return monsters;

}

void displayBattle(const Object& player, const std::vector<Object>& monsters)
{
	std::cout << player.name << ": " << player.health << std::endl
		<< "  Monsters: " << std::endl;
	for (int i{ 0 }; i < monsters.size(); i++)
	{
		std::cout << "   " << i + 1 << ". " << monsters[i].name << ": ";
		if (monsters.at(i).health <= 0)
			std::cout << "<DEAD> " << std::endl;
		else
			std::cout << monsters[i].health << std::endl;
	}
}

bool monsterAttack(Object& player, const std::vector<Object>& monsters)
{
	bool allDead{ true };
	std::bernoulli_distribution willAttack(.75);
	for (const auto& monster : monsters)
	{
		if (monster.health > 0)
		{
			allDead = false;
			if (willAttack(engine))
			{
				std::cout << monster.name << " attacks!" << std::endl;
				defend(player, attack(monster));
			}
			else
			{
				std::cout << monster.name << " twiddles its thumbs" << std::endl;
			}
		}
	}
	return allDead;
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

int attack(const Object& object)
{
	std::normal_distribution<double> damageDealt(object.strength, 2.0);
	std::cout << object.name << " deals ";
	return std::max(1, (int)damageDealt(engine));
}

void defend(Object& object, int damage)
{
	std::cout << damage << " damage to " << object.name << "!!!" << std::endl;
	object.health -= damage;
}

void heal(Object& object)
{
	std::normal_distribution<double> randomHeal(object.strength * 2.0, 3.0);
	int  amountHealed{ std::max(1, (int)randomHeal(engine)) };
	std::cout << object.name << " is healed by " << amountHealed << "hp!" << std::endl;
	object.health += amountHealed;
}