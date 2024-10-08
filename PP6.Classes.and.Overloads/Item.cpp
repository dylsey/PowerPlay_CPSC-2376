#include "Item.h"
#include <iostream>
#include <string>


Item::Item()
{

}

Item::Item(Type clasification, int bonusValue)
{
	this->clasification = clasification;
	this->bonusValue = bonusValue;

}

std::ostream& operator<<(std::ostream& out, const Item& item)
{
	switch (item.clasification)
	{
	case Item::Type::sword:
		out << "Sword";
		break;
	case Item::Type::armor:
		out << "Armor";
		break;
	case Item::Type::shield:
		out << "Shield";
		break;
	}
	out << " +" << item.bonusValue;
	return out;
}