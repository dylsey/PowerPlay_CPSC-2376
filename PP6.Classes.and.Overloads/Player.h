#pragma once
#include "Object.h"
#include <map>	
#include <vector>
#include <iostream>
#include <random> 


class Player: public Object
{
	public:
		//default constructor
		Player();
		//overloaded constructor
		Player(std::string name, int strength, int health, int level, std::map<Item::Type, Item> inventory);
		int spellPoints{ 10 };

		void playerAttack(const Object& player, std::vector<Object>& monsters);

		void levelUp(Object& player);


};

