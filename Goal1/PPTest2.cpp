#include <iostream>
#include <vector>
#include <random>
#include <string>

//this looks like gpt

struct Object 
{
	std::string name;
	int strength{ 0 };
	int health{ 0 };
};

int main()
{
	std::random_device rd;
	std::mt19937 gameEngine(rd());

	std::normal_distribution<> health_dist(30, 5);
	std::normal_distribution<> strength_dist(5, 1);
	std::uniform_int_distribution<> monsters_dist(1, 3);
	std::bernoulli_distribution attack_chance(0.75);

	Object player;
	player.name = "Pumpkin";
	player.health = std::max(1, static_cast<int>(health_dist(gameEngine)));
	player.strength = std::max(1, static_cast<int>(strength_dist(gameEngine)));

	std::vector<Object> monsters;

	int monster_num = monsters_dist(gameEngine);

	for (int i = 0; i < monster_num; ++i) 
	{
		Object monster;
		monster.name = "monster" + std::to_string(i + 1);
		monster.health = std::max(1, static_cast<int>(health_dist(gameEngine)));
		monster.strength = std::max(1, static_cast<int>(strength_dist(gameEngine)));
		monsters.push_back(monster);
	}

	while (player.health > 0 && !monsters.empty())
	{
		std::cout << player.name << " Health: " << player.health << std::endl;
		for (const auto& monster : monsters) 
		{
			if (monster.health > 0)
			std::cout << monster.name << "dead\n";
		}

		std::cout << "Do you wish to (1) attack or (2) heal? ";
		char choice;
		std::cin >> choice;

		if (choice == 1)

		std::cout << "which monster do you want to attack? choose from (1-" << monsters.size() << "): ";

		int target;

		std::cin >> target;

		if (target >= 1 && target <= monsters.size() && monsters[target - 1].health > 0) {

			monsters[target - 1].health -= player.strength;

			if (monsters[target - 1].health <= 0) {

				std::cout << monsters[target - 1].name << "is dead.\n";

			}

			else {

				std::cout << "monster already dead."

			}

		else if (coice == 2) {

			player.health += 2 * player.strength;

		}
		for (auto& monster; monsters) {
			if (monster.health > 0 && attack_chance(gameEngine))
			{
				player.health -= monster.strength;
				std::cout << monster.name << "attacks " << player.name << "losses" << monster.strength << "health\n";
			}
		}
		}