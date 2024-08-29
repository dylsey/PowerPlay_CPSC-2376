#include <iostream>
#include <string>
#include <vector>
#include <random>

struct Object
{
	std::string name;
	int strength{ 0 };
	int health{ 0 };
};

Object Player(std::string name)
{
	Object player;
	player.name = name;

	std::random_device rd;
	std::default_random_engine gen(rd());
	std::normal_distribution<double> strength_distr(5.0, 1.0);
	std::normal_distribution<double> health_distr(30.0, 5.0);

	double begin_strength = strength_distr(gen);
	double begin_health = health_distr(gen);

	if (begin_strength < 1.0)

	{
		player.strength = 1;
	}

	else
	{
		player.strength = double(begin_strength);
	}

	if (begin_health < 1.0)
	{
		player.health = 1;
	}
	else
	{
		player.health = double(begin_health);
	}
	return player;
};



Object Monsters(std::string name)

{
	Object monster;
	monster.name = name;
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::normal_distribution<double> strength_distr(5.0, 1.0);
	std::normal_distribution<double> health_distr(30.0, 5.0);

	double begin_strength = strength_distr(gen);
	double begin_health = health_distr(gen);

	if (begin_strength < 1.0)
	{
		monster.strength = 1;
	}
	else
	{
		monster.strength = double(begin_strength);
	}
	if (begin_health < 1.0)
	{
		monster.health = 1;
	}
	else
	{
		monster.health = double(begin_health);
	}
	return monster;
};

int main()
{
	Object player = Player("Sirius");

	std::cout << "Name:" << player.name << std::endl;
	std::cout << "Strength:" << player.strength << std::endl;
	std::cout << "Health:" << player.health << std::endl;


	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<int> monsters_distr(1, 3);

	int monsters_num = monsters_distr(gen);

	std::vector<Object> monsters;

	for (int i{ 1 }; i <= monsters_num; i++)
	{
		std::string monster_name = "Monster" + std::to_string(i);

		Object monster = Monsters(monster_name);

		monsters.push_back(monster);
	}

	for (Object monster : monsters)
	{
		std::cout << "Monster Name: " << monster.name << std::endl;
		std::cout << "Strength: " << monster.strength << std::endl;
		std::cout << "Health: " << monster.health << std::endl;
	}

	std::cout << "Do you want to Attack or Heal? 1 = Attack / 2 = Heal" << std::endl;

	int choice;

	std::cin >> choice;

	if (choice == 2)
	{
		player.health += 2 * player.strength;
		std::cout << "You healed" << std::endl;
	}
	else if (choice == 1)
	{
		std::cout << "Which monster would you like to attack?" << std::endl;
	}

};