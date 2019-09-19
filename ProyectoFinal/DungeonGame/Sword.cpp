#include "Sword.h"

Sword::Sword()
{
	_attack = 0;
	_magic_attack = 0;
	_speed = 0;
}

string Sword::getValues()
{
	string s;
	s = _text + "( " + to_string(_id) + " )\n";
	s += "\t Ataque: " + to_string(_attack) + "\n";
	s += "\t Defensa: " + to_string(_defense) + "\n";
	s += "\t Ataque Magico: " + to_string(_magic_attack) + "\n";
	s += "\t Defensa Magica: " + to_string(_magic_defense) + "\n";
	s += "\t Veocidad: " + to_string(_speed) + "\n";
	return s;
}

int Sword::getAttack() {
	return _attack;
}
int Sword::getDefense() {
	return _defense;
}
int Sword::getSpeed() {
	return _speed;
}
int Sword::getMagicAttack() {
	return _magic_attack;
}
int Sword::getMagicDefense() {
	return _magic_defense;
}