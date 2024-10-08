#pragma once
#include "Object.h"
#include <map>	
#include <vector>
#include <iostream>
#include <random> 
#include "Monster.h"



class Player: public Object
{
	public:
		//default constructor
		Player();
		//overloaded constructor
		Player(int strength, int health, int level, std::map<Item::Type, Item> inventory);
		int spellPoints{ 10 };

		void playerAttack(Object& player, std::vector<Monster>& monsters);

		void levelUp(Object& player);


};

