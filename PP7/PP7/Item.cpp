#include "Item.h"
#include <iostream>


Item::Item(itemType classification, int bonusValue) : classification{ classification }, bonusValue{ bonusValue }
{
}

Item::itemType Item::getClassification() const
{
	return classification;
}

int Item::getBonusValue() const
{
	return bonusValue;
}

std::ostream& operator<<(std::ostream& o, const Item& src)
{
	switch (src.getClassification())
	{
	case Item::itemType::armor:
		o << "Armor";
		break;
	case Item::itemType::shield:
		o << "Shield";
		break;
	case Item::itemType::sword:
		o << "Sword";
		break;
	}
	o << "+" << src.getBonusValue();
	return o;
}

bool operator<(const Item& srcL, const Item& srcR)
{
	return srcL.getBonusValue() < srcR.getBonusValue();
}

int& operator+=(int& srcL, const Item& srcR)
{
	srcL += srcR.getBonusValue();
	return srcL;
}

int operator+(const Item& srcL, const Item& srcR)
{
	return srcL.getBonusValue() + srcR.getBonusValue();
}