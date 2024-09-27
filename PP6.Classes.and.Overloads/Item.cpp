#include "Item.h"
#include <iostream>


void Item::printItem(const Item& item)
{
	switch (item.clasification)
	{
	case Type::sword:
		std::cout << "Sword";
		break;
	case Type::armor:
		std::cout << "Armor";
		break;
	case Type::shield:
		std::cout << "Shield";
		break;
	}
	std::cout << " +" << item.bonusValue;
}
