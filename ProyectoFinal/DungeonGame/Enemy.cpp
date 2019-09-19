#include "Enemy.h"
#include "Dungeon_Exception.h"

Enemy::Enemy(int life, int attack, int defense, int speed, int magic_attack, int magic_defense, int guts, int fangs, int bones, int metal) : 
		_life(life), _attack(attack), _defense(defense), _speed(speed), 
		_magic_attack(magic_attack), _magic_defense(magic_defense),
		_guts(guts), _fangs(fangs), _bones(bones), _metal(metal){
	if (_guts == 0 && _fangs == 0 && _bones == 0 && _metal == 0)
		_hasLoot = false;
	_isAlive = true;
	_isBoss = false;
	
}

void Enemy::getLoot(array<short, 4> * loot_list) {

	array<short, 4>::iterator i = loot_list->begin();
	(*i) += _guts;
	i++;
	(*i) += _fangs;
	i++;
	(*i) += _bones;
	i++;
	(*i) += _metal;
	i++;

	_guts = 0;
	_fangs = 0;
	_bones = 0;
	_metal = 0;

	_hasLoot = false;

}

int Enemy::getAttack() {
	return _attack;
}

int Enemy::getDefense() {
	return _defense;
}

int Enemy::getSpeed() {
	return _speed;
}

int Enemy::getMagicAttack() {
	return _magic_attack;
}

int Enemy::getMagicDefense() {
	return _magic_defense;
}

bool Enemy::isBoss() {
	return _isBoss;
}

bool Enemy::isAlive() {
	return _isAlive;
}

void Enemy::setLife(int damage) {
	_life -= damage;
	if (_life < 1) {
		_isAlive = false;
		throw Dungeon_Exception("Has matado a un enemigo");
	}
	throw Dungeon_Exception("Has dañado a un enemigo");
}

string Enemy::getData() {
	string s;
	s = "\t Ataque: " + to_string(_attack) + "\n";
	s += "\t Defensa: " + to_string(_defense) + "\n";
	s += "\t Ataque Magico: " + to_string(_magic_attack) + "\n";
	s += "\t Defensa Magica: " + to_string(_magic_defense) + "\n";
	s += "\t Velocidad: " + to_string(_speed) + "\n";
	return s;
}

