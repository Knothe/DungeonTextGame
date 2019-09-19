#pragma once
#include "Item.h"
class Sword : public Item
{
private:
	int _attack;
	int _magic_attack;
	int _speed;
	int _defense;
	int _magic_defense;
public:
	Sword();
	Sword(int id, std::string text, int attack, int magic_attack, int defense, int magic_defense, int speed) : Item(id, text), _attack(attack), _magic_attack(magic_attack), _speed(speed), _defense(defense), _magic_defense(magic_defense) {}

	string getValues() override;

	int getAttack();
	int getDefense();
	int getSpeed();
	int getMagicAttack();
	int getMagicDefense();


};

