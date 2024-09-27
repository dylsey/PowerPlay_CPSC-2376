#pragma once
#include <map>
#include <random>
#include <iostream>
#include "Item.h"

class Object
{
	public:
		//enum for object types
		enum class Type
		{
			player,
			slime,
			orc,
			sprite,
			dragon,
			numTypes
		};

		//default constructor
		Object();
		//conversion constructor

		//member variables	
		Type type;
		std::map<Item::Type, Item> inventory;
		int strength{ 0 };
		int health{ 0 };
		int level{ 0 };

		//getters
		int getStrength() const;
		int getHealth() const;
		int getLevel() const;
		Object::Type getType() const;

		//setters
		void setLevel(int level);
		void setStrength(int strength);
		void setHealth(int health);
		void setType(Type type);

			
		//member functions
		int calculateAC(const Object& object);
		void heal(Object& object);
		void printName(const Object& object);
		int attack(const Object& object);
		void defend(Object& object, int damage);

		friend std::ostream& operator<<(std::ostream& out, const Object& object);

};
//operator overloads



