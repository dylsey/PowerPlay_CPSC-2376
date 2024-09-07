#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <fstream>
using std::cout, std::cin, std::endl;
//provided struct for the game object


struct Object
{

	std::string name;

	int strength{ 0 };

	int health{ 0 };
};
std::vector<Object> loadMonsters(); // needs no parameters
void displayBattle(std::vector<Object>& monsters, Object& player); // needs a vector of monsters and a player object to display the battle
void monsterAttack(const std::vector<Object>& monsters, Object& player);
void playerAttack(std::vector<Object>& monsters, const Object& player);
int attack(const Object& attacker);
void defend(Object& defender, const int damage);
void heal(Object& player);
void clearScreen(); // needs no parameters

int main()
{
	Object player;
	player.name = "Janitorial Worker"; //give a fun name to the player
	// create a random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	// create a game object for the player
	while (player.strength < 1 || player.health < 1) // this loop should ensure that the player's strength and health are at least 1
	{
		// create a normal distribution for the player's strength with mean 5 and standard deviation 1
		std::normal_distribution<> playerStrength(5, 1);
		player.strength = (int)round(playerStrength(gen));
		// create a normal distribution for the player's health with mean 30 and standard deviation 5
		std::normal_distribution<> playerHealth(30, 5);
		player.health = (int)round(playerHealth(gen));
	}
	//open file for monsters, if not found, create it
	std::ifstream file("monsters.txt");
	if (!file.is_open())
	{
		std::ofstream file("monsters.txt");
	}
	//load monsters from file
	std::vector<Object> monsters{ loadMonsters() }; //I'm going to use the monsters the prof. created and just not generate new ones
	//gameplay loop
	while (true)
	{
		//clear the screen
		clearScreen();
		//display the battle
		displayBattle(monsters, player);
		//player's turn
		cout << "Player's turn! Choose your action" << endl;
		cout << "1. Attack" << endl;
		cout << "2. Heal" << endl;
		int playerChoice;
		cin >> playerChoice;
		cout << endl;
		//temp pause for debugging
		//system("pause");
		while (playerChoice != 1 && playerChoice != 2)
		{
			cout << "Invalid choice, try again: \n " << endl;
			cin >> playerChoice;
		}
		switch (playerChoice)
		{
		case 1:
			playerAttack(monsters, player);
			break;
		case 2:
			heal(player);
			break;
		}
		//monster's turn
		monsterAttack(monsters, player);
		//check if all monsters are dead
		bool allMonstersDead{ true };
		for (Object monster : monsters)
		{
			if (monster.health > 0)
			{
				allMonstersDead = false;
				break;
			}
		}
		//check gamestate - player dead, all monsters dead, or both
		if (player.health <= 0 && allMonstersDead)
		{
			cout << "You have died, but you cleared the dungeon... A valiant effort to be sure" << endl;
			break;
		}
		else if (player.health <= 0)
		{
			cout << "You have died... Game Over" << endl;
			break;
		}
		else if (allMonstersDead)
		{
			cout << "You have cleared the dungeon! Congratulations!" << endl;
			break;
		}
		else
		{
			cout << "You are still alive and there are still monsters to fight! Continue the battle!" << endl;
			cout << "Press enter to continue..." << endl;
			std::cin.ignore();
			std::cin.get();
		}
		//clear the screen
		clearScreen();
	}
	return 0;
}
//should be able to load monsters from a file - testing needed
std::vector<Object> loadMonsters()
{
	// create a vector of objects for the monsters
	std::vector<Object> tempMonsters;
	std::ifstream file("monsters.txt");
	// load the number of monsters from the first line of the file
	int numMonsters;
	file >> numMonsters;
	// create the monsters and add them to the vector
	for (int i{ 0 }; i < numMonsters; i++)
	{
		Object monster;
		// load the monster's name from the file
		file >> monster.name;
		// load the monster's strength and health from the file
		file >> monster.strength;
		file >> monster.health;
		tempMonsters.push_back(monster);
	}
	// test print all monsters from the file
	/*for (int i{ 0 }; i < monsters.size(); i++)
	{
	cout << "Monster " << i + 1 << "'s name: " << monsters[i].name << endl;
	cout << "Monster " << i + 1 << "'s strength: " << monsters[i].strength << endl;
	cout << "Monster " << i + 1 << "'s health: " << monsters[i].health << endl;
	}*/

	return tempMonsters;
}
void monsterAttack(const std::vector<Object>& monsters, Object& player)
{
	// monsters attack the player
	// create a random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	//all monsters attack the player bernoulli distribution for chance at 75% chance to attack
	std::bernoulli_distribution attackChance(0.75);
	for (Object monster : monsters)
	{
		if (monster.health <= 0) //if the monster is dead, skip the attack
		{
			continue;
		}
		if (attackChance(gen))
		{
			defend(player, attack(monster));
		}
	}
}
void playerAttack(std::vector<Object>& monsters, const Object& player)
{
	//player attacks the monster
	cout << "Player attacks!" << endl;
	int monsterChoice; //moved out of loop for scope
	while (true)
	{
		cout << "Choose a monster to attack: " << endl;
		for (int i{ 0 }; i < monsters.size(); i++)
		{
			cout << i + 1 << ". " << monsters[i].name << endl;
		}
		cin >> monsterChoice;
		cout << endl;
		//temp pause for debugging
		//system("pause");
		while (monsterChoice < 1 || monsterChoice > monsters.size())
		{
			cout << "Invalid choice, try again: \n " << endl;
			cin >> monsterChoice;
			cout << endl;
		}
		if (monsters[monsterChoice - 1].health <= 0)
		{
			cout << "That monster is already dead" << endl;
		}
		else
		{
			//if the choice is valid and the monster is alive, break the loop
			break;
		}
	}
	//player attacks the monster
	defend(monsters[monsterChoice - 1], attack(player));
}
int attack(const Object& attacker)
{
	// create a random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	//normal distribution for the attack calculation mean = strength, standard deviation = 2
	std::normal_distribution<> damgageCalc(attacker.strength, 2);
	int damage{ (int)round(damgageCalc(gen)) };
	if (damage <= 0)
	{
		damage = 0;
		cout << attacker.name << " missed!" << endl;
	}
	else
	{
		cout << attacker.name << " attacks for " << damage << " damage!" << endl;
		cout << endl;
	}
	return damage;
}
void defend(Object& defender, const int damage)
{
	//subtract the damage from the defender's health
	defender.health -= damage;
	//display the damage taken
	cout << defender.name << " took " << damage << " damage!" << endl;
	cout << endl;
}
void heal(Object& player)
{
	// create a random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	//normal distribution for the heal calculation mean = strength, standard deviation = 2
	std::normal_distribution<> healCalc((player.strength * 2), 3);
	int heal{ (int)round(healCalc(gen)) };
	cout << player.name << " heals for " << heal << " health!" << endl;
	cout << endl;
	player.health += heal;
}
//display the battle - working properly
void displayBattle(std::vector<Object>& monsters, Object& player)
{
	//print the player's health and strength
	cout << player.name << "'s health : " << player.health << endl;
	cout << player.name << "'s strength: " << player.strength << endl;
	cout << endl;

	//print the monsters' health and strength
	for (Object monster : monsters)
	{
		if (monster.health <= 0) //if the monster is dead, display health as DEAD
		{
			cout << monster.name << "'s health: DEAD" << endl;
			cout << monster.name << "'s strength: " << monster.strength << endl;
			cout << endl;
			continue;
		}
		else

		{
			cout << monster.name << "'s health: " << monster.health << endl
			cout << monster.name << "'s strength: " << monster.strength << endl;
		}
		cout << endl;
	}
}
//clear the screen - working properly - ansi escape codes used - I used this all throughout programming one, if I need to add my source again 
// for this class, please tell me
void clearScreen()
{
	//clear the screen using ansi escape codes
	cout << "\033[2J\033[1;1H";
}