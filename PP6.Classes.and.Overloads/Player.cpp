#include "Player.h"
#include <iostream>
#include <random>

std::random_device seed;
std::default_random_engine engine(seed());

Player::Player()
{
}

Player::Player(std::string name, int strength, int health, int level, std::map<Item::Type, Item> inventory)
{

}

void Player::playerAttack(const Object& player, std::vector<Object>& monsters)
{
}

void Player::levelUp(Object& player)
{
	player.level++;
	std::normal_distribution<double> randomHealth(20.0 + player.level * 5, 5.0);
	player.health += std::max(1, (int)randomHealth(engine));

	std::normal_distribution<double> randomStrength(3.0 + player.level, 1.0);
	player.strength += std::max(1, (int)randomStrength(engine));

	//grab new item.
	std::uniform_int_distribution<int> randomItem(0, (int)Item::Type::numTypes - 1);
	std::normal_distribution<double> randomBonus((double)player.level, (double)player.level / 2);
	Item found{ (Item::Type)randomItem(engine), std::max(1, (int)randomBonus(engine)) };

	std::cout << "You found a " << item;
	//printItem(found);
	std::cout << "!!!!" << std::endl;
	if (
		auto haveOne{ player.inventory.find(found.clasification) };
		haveOne == player.inventory.end()
		|| player.inventory[found.clasification].bonusValue < found.bonusValue
		)
	{
		std::cout << "You keep the shiny new toy!" << std::endl;
		player.inventory[found.clasification] = found;
	}
	else
	{
		std::cout << "You toss aside the ugly old thing!" << std::endl;
	}
}

