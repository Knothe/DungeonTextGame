#include "Shield.h"

Shield::Shield()
{
	_defense = 0;
}

/*
@return defense value
*/
int Shield::getDefense() {
	return _defense;
}

string Shield::getValues() {
	string s;

	s = _text + "( " + to_string(_id) + " )\n";
	s += "\t Ataque: 0\n";
	s += "\t Defensa: " + to_string(_defense) + "\n";
	s += "\t Ataque Magico: 0\n";
	s += "\t Defensa Magica: " + to_string(_magic_defense) + "\n";
	s += "\t Veocidad:" + to_string(_speed) + "\n";

	return s;
}

int Shield::getSpeed() {
	return _speed;
}
int Shield::getMagicDefense() {
	return _magic_defense;
}