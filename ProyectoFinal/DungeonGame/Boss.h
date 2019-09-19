#pragma once
#include "Enemy.h"
#include "Sword.h"
#include "Shield.h"
#include <array>
#include <string>

using std::array;

class Boss : public Enemy
{
protected:
	Sword* _sword;
	Shield* _shield;

public:
	Boss(int, int, int, int, int, int, int, int, int, int, Sword*, Shield*);
	Sword* getSword();
	Shield* getShield();
	int getAttack();
	int getDefense();
	int getSpeed();
	int getMagicAttack();
	int getMagicDefense();
	string getData();
	void setLife(int damage);
};

