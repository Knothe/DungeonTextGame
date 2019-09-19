#include "Boss.h"
#include "Dungeon_Exception.h"

Boss::Boss(int life, int attack, int defense, int speed, int magic_attack, int magic_defense, int guts, int fangs, int bones, int metal, Sword* sword, Shield* shield) :
	Enemy(life, attack, defense, speed, magic_attack, magic_defense, guts, fangs, bones, metal) {
	_isBoss = true;
	_hasLoot = true;
	_isAlive = true;
	_sword = sword;
	_shield = shield;

}

int Boss::getAttack() {
	int value = _attack;
	if(_sword)
		value += _sword->getAttack();
	return value;
}

int Boss::getDefense() {
	int value = _defense;
	if(_sword)
		value += _sword->getDefense();
	if (_shield)
		value += _shield->getDefense();
	return value;
}

int Boss::getSpeed() {
	int value = _defense;
	if(_sword)
		value += _sword->getSpeed();
	if (_shield)
		value += _shield->getSpeed();
	return value;
}

int Boss::getMagicAttack() {
	int value = _magic_attack;
	if(_sword)
		value += _sword->getMagicAttack();
	return value;
}

int Boss::getMagicDefense() {
	int value = _magic_defense;
	if(_sword)
		value += _sword->getMagicDefense();
	if (_shield)
		value += _shield->getMagicDefense();
	return value;
}

Sword* Boss::getSword() {
	return _sword;
}

Shield* Boss::getShield() {
	return _shield;
}

string Boss::getData() {
	string s;
	s = "\t Ataque: " + to_string(_attack) + "\n";
	s += "\t Defensa: " + to_string(_defense) + "\n";
	s += "\t Ataque Magico: " + to_string(_magic_attack) + "\n";
	s += "\t Defensa Magica: " + to_string(_magic_defense) + "\n";
	s += "\t Veocidad: " + to_string(_speed) + "\n";
	if (_sword) {
		s+= "~~Espada: ";
		s +=_sword->getValues();
	}
	if (_shield) {
		s += "~~Escudo: ";
		s +=_shield->getValues();
	}
	return s;
}

void Boss::setLife(int damage) {
	_life -= damage;
	if (_life < 1) {
		_isAlive = false;
		throw Dungeon_Exception("Has matado al boss");
	}
	throw Dungeon_Exception("Has dañado al boss");

}
