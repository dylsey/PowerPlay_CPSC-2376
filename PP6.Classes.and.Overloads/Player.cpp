#include "Player.h"

Player::Player()
{
}

Player::Player(std::string name, int strength, int health, int level, std::map<Item::Type, Item> inventory)
{
	this->name = Object::Type::player;
	this->strength = strength;
	this->health = health;
	this->level = level;
	this->inventory = inventory;
}

void Player::playerAttack(const Object& player, std::vector<Object>& monsters)
{
}

void Player::levelUp(Object& player)
{
}

