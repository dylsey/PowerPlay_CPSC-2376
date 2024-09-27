#pragma once

class Item
{
	public:
		enum class Type { sword, armor, shield, numTypes };
		Type clasification;
		int bonusValue;
		void printItem(const Item& item);

};

