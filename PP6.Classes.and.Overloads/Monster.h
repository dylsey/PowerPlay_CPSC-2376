#pragma once
#include "Object.h"
#include <vector>


class Monster: public Object
{
	public: 
		Monster();
		Monster(Object::Type type, int strength, int health, int level);
		

		void monsterAttack(Object& player,  std::vector<Monster>& monsters);

		std::vector<Monster> createMonsters(const Object& player);


};

