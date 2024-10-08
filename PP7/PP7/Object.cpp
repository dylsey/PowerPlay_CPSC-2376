#include <random>
#include <iostream>
#include "Object.h"


class Item;

std::random_device Object::seed;
std::default_random_engine Object::engine(seed());

Object::Object(Type name, int strength, int health, int level) : name{ name }, strength{ strength }, health{ health }, level{ level }
{
}

bool Object::isDead()
{
	if (health <= 0)
	{
		return true;
	}
	return false;
}

Object::Type Object::getName() const
{
	return name;
}

int Object::getLevel() const
{
	return level;
}

int Object::getHealth() const
{
	return health;
}

void Object::print(std::ostream& o) const
{
	o << "L: " << level << " " << "h: " << health;
}

int Object::damageDone(int modification) const
{
	int potentialDamage{ strength };
	std::normal_distribution<double> damageDealt(potentialDamage, 2.0);

	std::cout << *this << " deals ";
	return std::max(1, (int)damageDealt(engine));
}

int Object::damageTaken(int damageDone, int AC)
{

	std::normal_distribution<double> defense(AC, 1.0 / level);
	int actualDamage{ std::max(0, damageDone - (int)defense(engine)) };
	std::cout << damageDone << " damage to ";

	std::cout << *this << "!!!" << std::endl;
	health -= actualDamage;

	return actualDamage;
}

std::ostream& operator<<(std::ostream& o, const Object& src)
{
	o << "L:" << src.getLevel() << " ";
	switch (src.getName())
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
	o << " h:" << src.getHealth();
	return o;
}