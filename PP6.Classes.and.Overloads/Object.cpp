#include "Object.h"
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <random>

std::random_device seed;
std::default_random_engine engine(seed());

Object::Object() {}


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
	printName(object);
	std::cout << " is healed by " << amountHealed << "hp!" << std::endl;
	object.health += amountHealed;
}

void Object::printName(const Object& object)
{
	std::cout << "Level:" << object.level << " ";
	switch (object.type)
	{
	case Object::Type::player:
		std::cout << "Player";
		break;
	case Object::Type::slime:
		std::cout << "Slime";
		break;
	case Object::Type::orc:
		std::cout << "Orc";
		break;
	case Object::Type::sprite:
		std::cout << "Sprite";
		break;
	case Object::Type::dragon:
		std::cout << "Dragon";
		break;
	}
}

int Object::attack(const Object& object)
{
	int potentialDamage{ object.strength };
	if (auto sword{ object.inventory.find(Item::Type::sword) }; sword != object.inventory.end())
	{
		potentialDamage += sword->second.bonusValue;
	}
	std::normal_distribution<double> damageDealt(potentialDamage, 2.0);

	printName(object);
	std::cout << " deals ";
	return std::max(1, (int)damageDealt(engine));
}

void Object::defend(Object& object, int damage)
{
	std::normal_distribution<double> defense(calculateAC(object), 1.0 / object.level);
	damage = std::max(0, damage - (int)defense(engine));
	std::cout << damage << " damage to ";
	printName(object);
	std::cout << "!!!" << std::endl;
	object.health -= damage;
}

std::ostream& operator<<(std::ostream& out, const Object& object)
{
	// TODO: insert return statement here

}
