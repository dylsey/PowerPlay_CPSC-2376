#pragma once
#include "Object.h"
#include <vector>


class Monster: public Object
{
	public: 
		Monster();
		Monster(Object::Type type, int strength, int health, int level);

		std::vector<Object> createMonsters(const Object& player);


};

