#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>

class Item {
public:
	enum class Type { sword, armor, shield, numTypes };
	Type classification;
	int bonusValue;

	friend std::ostream& operator<<(std::ostream& os, const Item& item) {
		os << "Item: ";
		switch (item.classification) {
		case Type::sword: os << "Sword"; break;
		case Type::armor: os << "Armor"; break;
		case Type::shield: os << "Shield"; break;
		default: os << "Unknown";
		}
		os << ", Bonus: +" << item.bonusValue;
		return os;
	}

	bool operator<(const Item& other) const {
		return bonusValue < other.bonusValue;
	}

	int operator+=(int bonus) {
		bonusValue += bonus;
		return bonusValue;
	}
};

class Object {
public:
	enum class Type { player, slime, orc, sprite, dragon, numTypes };
	Type name;
	int strength{ 0 };
	int health{ 0 };
	int level{ 0 };
	std::map<Item::Type, Item> inventory;

	friend std::ostream& operator<<(std::ostream& os, const Object& obj) {
		os << "Object Type: ";
		switch (obj.name) {
		case Object::Type::player: os << "Player"; break;
		case Object::Type::slime: os << "Slime"; break;
		case Object::Type::orc: os << "Orc"; break;
		case Object::Type::sprite: os << "Sprite"; break;
		case Object::Type::dragon: os << "Dragon"; break;
		default: os << "Unknown";
		}
		os << ", Strength: " << obj.strength;
		os << ", Health: " << obj.health;
		os << ", Level: " << obj.level;
		return os;
	}
};

class Player : public Object {
public:
	int spellPoints{ 0 };

	Player() {
		name = Object::Type::player;
	}

	void heal() {
		if (spellPoints >= 2) {
			health += 10;
			spellPoints -= 2;
			std::cout << "Healed 10 HP, remaining spell points: " << spellPoints << std::endl;
		}
		else {
			std::cout << "Not enough Spell Points to heal!" << std::endl;
		}
	}
};

class Monster : public Object {
public:
	int AC{ 0 };

	Monster(Object::Type type) {
		name = type;
	}
};

int main() {
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<> randomBonus(1, 10);

	Player player;
	player.strength = 10;
	player.health = 50;
	player.level = 5;
	player.spellPoints = 5;

	Monster orc(Object::Type::orc);
	orc.strength = 8;
	orc.health = 30;
	orc.level = 4;

	Item sword{ Item::Type::sword, randomBonus(engine) };
	Item shield{ Item::Type::shield, randomBonus(engine) };

	player.inventory[sword.classification] = sword;
	orc.inventory[shield.classification] = shield;

	std::cout << player << std::endl;
	std::cout << orc << std::endl;

	if (sword < shield) {
		std::cout << "Shield is better than Sword" << std::endl;
	}
	else {
		std::cout << "Sword is better than Shield" << std::endl;
	}

	sword += 2;
	std::cout << "Sword after bonus: " << sword << std::endl;

	player.heal();

	return 0;
}
