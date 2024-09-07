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
// Each function includes pass by references for editing the original sources rather than their copies.

void loadMonsters(std::vector<Object>& monsters);
void displayBattle(Object& player, std::vector<Object>& monsters);
void monsterAttack(std::vector<Object>& monsters, Object& player, std::default_random_engine& engine, bool& allDead);
void playerAttack(std::vector<Object>& monsters, Object& player, std::default_random_engine& engine, bool& allDead);
int attack(const Object& attacker, std::default_random_engine& engine); 
/* Made the type int as it needs to return the amount of damage
dealt, which will be an integer, to the calling functions. I also made
the reference constant because it shouldn't modify anything and will result in an error
left non-const. */
void defend(Object& defender, int damage);
void heal(Object& player, std::default_random_engine& engine);

int main()
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::normal_distribution<double> randomHealth(30.0, 5.0);
	std::normal_distribution<double> randomStrength(5.0, 1.0);

	Object player
	{
		"Mr. Orme",
		std::max(1, (int)randomStrength(engine)),
		std::max(1, (int)randomHealth(engine))
	};

	std::vector<Object> monsters;

	loadMonsters(monsters);

	std::cout << monsters.size() << " monster(s) approaches!!" << std::endl;

	bool allDead{ false };

	while (player.health > 0 && !allDead)
	{
		displayBattle(player, monsters);
		std::cout << "What do you do? (a)ttack (h)eal ";
		char command{ };
		std::cin >> command;
		switch (command)
		{
		case 'a':
		{
			playerAttack(monsters, player, engine, allDead);
			break;
		}
		case 'h':
		{
			heal(player, engine);
			break;
		}
		default:
		{
			std::cout << "please enter a or h" << std::endl;
			break;
		}
		monsterAttack(monsters, player, engine, allDead);
		system("PAUSE");
		system("CLS");
		}
		if (player.health <= 0)
		{
			std::cout << "You Have Died" << std::endl;
		}
		if (player.health <= 0 && allDead)
		{
			std::cout << "BUT" << std::endl;
		}
		if (allDead)
		{
			std::cout << "You have killed the monsters!!!" << std::endl;
		}
		system("PAUSE");
	}
}

void loadMonsters(std::vector<Object>& monsters)
{
	std::ifstream inf{ "monsters.txt" }; /* Reads from the monsters.txt file in a "downward" order
	to where each monster's details appear in the right sections. */
	if (!inf)
	{
		std::cerr << "Unable to read monsters.txt!\n";
		return;
	}
		int totalMnstrs;
		inf >> totalMnstrs; // Referring to the comment above, because 3 is the first line, it is recognized as this integer.

	for (int i = 0; i < totalMnstrs; ++i)
	{
		Object monster;
		inf >> monster.name >> monster.strength >> monster.health;
		monsters.push_back(monster); // Adds each monster to std::vector<Object> through the monsters reference
	}
}

void displayBattle(Object& player, std::vector<Object>& monsters)
{
	std::cout << player.name << ": " << player.health << std::endl
		<< " Monsters: " << std::endl;
	for (int i{ 0 }; i < monsters.size(); i++)
	{
		std::cout << "  " << i + 1 << ". " << monsters[i].name << ": ";

		if (monsters.at(i).health <= 0)
			std::cout << "<DEAD> " << std::endl;
		else
			std::cout << monsters[i].health << std::endl;
	}
}

void monsterAttack(std::vector<Object>& monsters, Object& player, std::default_random_engine& engine, bool& allDead)
{
	std::bernoulli_distribution willAttack(.75);
	allDead = true;
	for (const auto& monster : monsters)
	{
		if (monster.health > 0)
		{
			allDead = false;
			if (willAttack(engine))
			{
				defend(player, attack(monster, engine));
			}
			else
			{
				std::cout << monster.name << " twiddles its thumbs" << std::endl;
			}
		}
	}
}

void playerAttack(std::vector<Object>& monsters, Object& player, std::default_random_engine& engine, bool& allDead)
{
	std::cout << "Which Monster: ";
	int monsterNum{ 0 };
	std::cin >> monsterNum;

	if (monsterNum > 0 && monsterNum <= monsters.size())
	{
		if (monsters.at(monsterNum - 1).health > 0)
			defend(monsters.at(monsterNum - 1), attack(player, engine));
	}
}

int attack(const Object& attacker, std::default_random_engine& engine)
{
	std::normal_distribution<double> dmgdlt(attacker.strength, 2.0);
	int damage = std::max(1, static_cast<int> (dmgdlt(engine))); 
	/* Used std::max to ensure the damage is greater than 1.
	I also used static_cast to convert the double to an integer. */
	std::cout << attacker.name << " deals " << damage << " damage!\n";
	return damage;
}

void defend(Object& defender, int damage)
{
	defender.health -= damage;
	std::cout << damage << " damage to " << defender.name << "!!!\n";
}

void heal(Object& player, std::default_random_engine& engine)
{
	std::normal_distribution<double> addhp(player.strength * 2, 2.0);
	int hpamount = std::max(1, static_cast<int> (addhp(engine)));
	player.health += hpamount;
	std::cout << player.name << " gained " << hpamount << " HP!\n";
}