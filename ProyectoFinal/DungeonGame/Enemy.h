#pragma once
#include <string>
#include <iostream>
#include <array>

using std::array;
using std::string;
using std::to_string;

class Enemy
{
protected:
	bool _isBoss, _isAlive, _hasLoot;
	int _life;
	unsigned int _attack;
	unsigned int _defense;
	unsigned int _speed;
	unsigned int _magic_attack;
	unsigned int _magic_defense;

	unsigned int _guts;
	unsigned int _fangs;
	unsigned int _bones;
	unsigned int _metal;

public:
	Enemy(int life, int attack, int defense, int speed, int magic_attack, int magic_defense, int guts, int fangs, int bones, int metal);
	void getLoot(array<short, 4> * loot_list);
	 int getAttack();
	 int getDefense();
	 int getSpeed();
	 int getMagicAttack();
	 int getMagicDefense();
	 string getData();
	bool isBoss();
	bool isAlive();
	void setLife(int damage);
	
};

