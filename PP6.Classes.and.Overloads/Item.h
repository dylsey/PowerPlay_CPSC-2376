#pragma once
#include <iostream>

class Item
{
	public:
		enum class Type 
		{ 
			sword, 
			armor, 
			shield, 
			numTypes 
		};

		Item();

		Type clasification;
		int bonusValue;
		//void printItem(const Item& item);

		friend std::ostream& operator<<(std::ostream& out, const Item& item);

};

