#pragma once
#include <iostream>
#include <string>
#include <map>
#include <random>

class Player;
class Monster;

class Object
{
	public:
		static std::random_device seed;
		static std::default_random_engine engine;
		enum class Type { player, slime, orc, sprite, dragon, numTypes };

		Object() {}
		Object(Type name, int strength, int health, int level);

		bool isDead();
		Type getName() const;
		int getLevel() const;
		int getHealth() const;

		virtual int attack() const = 0;
		//Player: calls damageDone passing in bonusValue for sword or 0.. returns value returned by damageDone
		//Monster: calls damageDone(0) and returns the returned value.
		virtual void defend(int damage) = 0;
		//Player: calculates AC, passes along damage and AC to damageTaken
		//Monster : calls damageTaken(damage, AC);
		virtual void update(Player& player, std::vector<Monster>& monsters) = 0;
		//Player: lines 44 - 60 from Goal.6.cpp goes here.The part dealing with attacking vs healing.Also playerAttack function is no longer a function, just put the code in the ‘a’ case.
		//Monster: The part inside the for_each goes here.for_each now just calls the update…
		virtual void print(std::ostream& o) const;
		/*the overload of the << operator will call this to make sure it the proper one is called!*/



	protected:
		Type name{ Type::numTypes };
		int strength{ 0 };
		int health{ 0 };
		int level{ 0 };

		int damageDone(int modification) const;
		//does the common bits for attack.Monsters pass in 0, player based on sword
		int damageTaken(int damageDone, int AC);
		//does the common bits for defend.


};

std::ostream& operator<< (std::ostream& o, const Object& src);


