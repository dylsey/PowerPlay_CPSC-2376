#pragma once
#include <iostream>



class Item
{
public:
	Item() {};
	enum class itemType { sword, armor, shield, numTypes };
	Item(itemType classification, int bonusValue);

	itemType getClassification() const;
	int getBonusValue() const;
private:
	itemType classification{ itemType::numTypes };
	int bonusValue{ 0 };
};

std::ostream& operator<< (std::ostream& o, const Item& src);


std::ostream& operator<< (std::ostream& o, const Item& src);
bool operator< (const Item& srcL, const Item& srcR);
int& operator+=(int& srcL, const Item& srcR);

