#include "Object.h"
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <random>

std::random_device seed;
std::default_random_engine engine(seed());

Object::Object()
{
}

Object::Object(Type type, int strength, int health, int level, std::map<Item::Type, Item> inventory)
	: type{ type }, strength{ strength }, health{ health }, level{ level }, inventory{ inventory }
{
}


int Object::getStrength() const
{
	return strength;
}

int Object::getHealth() const
{
	return health;
}

int Object::getLevel() const
{
	return level;
}

Object::Type Object::getType() const
{
	return Type();
}

void Object::setLevel(int level)
{
	this->level = level;
}

void Object::setStrength(int strength)
{
	this->strength = strength;
}

void Object::setHealth(int health)
{
	this->health = health;
}

void Object::setType(Type type)
{
	this->type = type;
}

int Object::calculateAC(const Object& object)
{
	int AC{ 0 };
	if (auto armor{ object.inventory.find(Item::Type::armor) }; armor != object.inventory.end())
	{
		AC += armor->second.bonusValue;
	}
	if (auto shield{ object.inventory.find(Item::Type::shield) }; shield != object.inventory.end())
	{
		AC += shield->second.bonusValue;
	}
	return AC;
}

void Object::heal(Object& object)
{
	std::normal_distribution<double> randomHeal(object.strength, 3.0);
	int  amountHealed{ std::max(1, (int)randomHeal(engine)) };
	std::cout << object << " is healed by " << amountHealed << "hp!" << std::endl;
	object.health += amountHealed;
}

int Object::attack(Object& object)
{
	int potentialDamage{ object.strength };
	if (auto sword{ object.inventory.find(Item::Type::sword) }; sword != object.inventory.end())
	{
		potentialDamage += sword->second.bonusValue;
	}
	std::normal_distribution<double> damageDealt(potentialDamage, 2.0);

	std::cout << object << " deals ";
	return std::max(1, (int)damageDealt(engine));
}

void Object::defend(Object& object, int damage)
{
	std::normal_distribution<double> defense(calculateAC(object), 1.0 / object.level);
	damage = std::max(0, damage - (int)defense(engine));
	std::cout << damage << " damage to " << object << std::endl;
	std::cout << "!!!" << std::endl;
	object.health -= damage;
}

std::ostream& operator<<(std::ostream& out, const Object& object)
{
	switch (object.type)
	{
	case Object::Type::player:
		out << "Player";
		break;
	case Object::Type::slime:
		out << "Slime";
		break;
	case Object::Type::orc:
		out << "Orc";
		break;
	case Object::Type::sprite:
		out << "Sprite";
		break;
	case Object::Type::dragon:
		out << "Dragon";
		break;
	}

	return out; 
}
