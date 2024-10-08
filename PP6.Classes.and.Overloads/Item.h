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

		Item(Type clasification, int bonusValue);

		Type clasification;
		int bonusValue{0};


		friend std::ostream& operator<<(std::ostream& out, const Item& item);

};

