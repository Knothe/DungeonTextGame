#pragma once
#include "Item.h"
class Shield : public Item
{
private:
	int _defense;
	int _magic_defense;
	int _speed;


public:
	Shield();
	Shield(int id, std::string text, int defense, int magic_defense, int speed) : Item(id, text), _defense(defense), _magic_defense(magic_defense), _speed(speed) {}

	string getValues() override;

	int getDefense();
	int getSpeed();
	int getMagicDefense();
};

