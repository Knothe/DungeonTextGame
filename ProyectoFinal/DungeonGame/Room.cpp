#include "Room.h"
#include <typeinfo>
#include <stdlib.h>  
#include <time.h>    

Room::Room(std::string text, bool enemy, short id, short roomsForEnemy) : _text(text), _id(id), _roomsForEnemy(roomsForEnemy){ 
	if (!enemy) {
		_enemy_list = NULL;
	}
	else {
		_enemy_list = new std::forward_list<Enemy*>;
	}
}

/*
@param d es un apuntador a una puerta, la cual se agregara al cuarto
*/
void Room::addDoor(Door* d){
	_door_list.push_front(d);
}

void Room::addEnemy(Enemy* e) {
	_enemy_list->push_front(e);
}

void Room::addItem(Item* i){
	_item_list.push_back(i);
}

string Room::getData()
{
	string s;
	Door* d;
	try{
		s = "------------- Cuarto: " + to_string(_id) + " -------------\n";
		s += _text + "\n";
		s += "Puertas: ";


		for (std::forward_list<Door*>::iterator i = _door_list.begin(); i != _door_list.end(); i++) {
			d = *i;
			s += to_string(d->getId()) + "\t";
		}
		s += "\n";
		for (int i = 0; i < _item_list.size(); i++) {
			if (Sword* e = dynamic_cast<Sword*>(_item_list[i])) {
				s += "~~Espada: " + e->getValues() + "\n";
			} else if (Shield * _s = dynamic_cast<Shield*>(_item_list[i])) {
				s += "~~Escudo: " + _s->getValues() + "\n";
			}
			else if (Key * k = dynamic_cast<Key*>(_item_list[i])) {
				s += "~~Llave: " + k->getValues() + "\n";
			}
		}
		if (hasEnemy())
			s += "~~ Hay enemigos\n";
		else
			s += "~~ No hay enemigos\n";
	} catch (std::exception & e) {
		cout << "Room.printData(): " << e.what() << std::endl;
	}
	return s;
	
}

/*
@param n es el id de la puerta
@return apuntador a la puerta elegida
*/
Door* Room::getDoor(int n, bool hasKey, int bosses){
	
	Door* d;

	for (std::forward_list<Door*>::iterator i = _door_list.begin(); i != _door_list.end(); i++){
		d = *i;
		if (n == d->getId()){
			if (n == 35) {
				if (bosses == 4)
					return d;
				else
					throw Dungeon_Exception("No has conseguido a todos tus compañeros");
			}
			else {
				if (!d->isClosed())
					return d;
				else if (d->isClosed() && hasKey)
					return d;
				else
					throw Dungeon_Exception("No tienes la llave");
			}
				
		}
	}
	throw Dungeon_Exception("En este cuarto no está esa puerta");

}

Sword* Room::grabSword(int id) {
	for (int i = 0; i < _item_list.size(); i++) {
		if (Sword * e = dynamic_cast<Sword*>(_item_list[i])) {
			if (e->getID() == id) {
				_item_list.erase(_item_list.begin() + i);
				return e;
			}
		}
		throw Dungeon_Exception("No esta esa espada");
	}
}

Shield* Room::grabShield(int id) {
	for (int i = 0; i < _item_list.size(); i++) {
		
		if (Shield * s = dynamic_cast<Shield*>(_item_list[i])) {
			if (s->getID() == id) {
				_item_list.erase(_item_list.begin() + i);
				return s;
			}
		}
	}
	throw Dungeon_Exception("No esta ese escudo");
}

Key* Room::grabKey(int id) {
	for (int i = 0; i < _item_list.size(); i++) {
		
		if (Key * k = dynamic_cast<Key*>(_item_list[i])) {
			if (k->getID() == id) {
				_item_list.erase(_item_list.begin() + i);
				return k;
			}
		}
	}
	throw Dungeon_Exception("No esta esa llave");
}

Sword* Room::grabSword() {
	for (int i = 0; i < _item_list.size(); i++) {
		if (Sword * e = dynamic_cast<Sword*>(_item_list[i])) {
				_item_list.erase(_item_list.begin() + i);
				return e;
		}
	}
	throw Dungeon_Exception("No hay espada");
}

Shield* Room::grabShield() {
	for (int i = 0; i < _item_list.size(); i++) {
		if (Shield * s = dynamic_cast<Shield*>(_item_list[i])) {
				_item_list.erase(_item_list.begin() + i);
				return s;
		}
	}
	throw Dungeon_Exception("No hay escudo");
}

Key* Room::grabKey() {
	for (int i = 0; i < _item_list.size(); i++) {
		if (Key * k = dynamic_cast<Key*>(_item_list[i])) {
			_item_list.erase(_item_list.begin() + i);
			return k;
		}
	}
}

bool Room::hasBoss() {
	if (hasEnemy()) {
		for (forward_list<Enemy*>::iterator i = _enemy_list->begin(); i != _enemy_list->end(); i++) {
			if ((*i)->isBoss())
				return true;
		}
	}
	return false;
}

bool Room::hasEnemy() {
	if (_enemy_list) {
		for (forward_list<Enemy*>::iterator i = _enemy_list->begin(); i != _enemy_list->end(); i++) {
			if ((*i)->isAlive())
				return true;
		}
	}
	return false;
	
}

forward_list<Enemy*>* Room::getEnemyList(){
	return _enemy_list;
}

string Room::printEnemies() {
	string s;
	s = "";
	if (_enemy_list) {
		for (forward_list<Enemy*>::iterator i = _enemy_list->begin(); i != _enemy_list->end(); i++) {
			if ((*i)->isBoss()) {
				Boss* b = (Boss*)&* (*i);
				s += "-Boss: \n";
				if (b->isAlive())
					s += b->getData();
				else
					s += "Esta muerto\n";
			}
			else {
				s += "-Minion: \n";
				if ((*i)->isAlive())
					s += (*i)->getData();
				else
					s += "Esta muerto\n";
			}
		}
	}
	else
		throw Dungeon_Exception("No hay enemigos aqui");
	return s;
}

Sword* Room::getItem(Sword*, int n) {
	if (n != -1)
		return grabSword(n);
	else
		return grabSword();
}

Shield* Room::getItem(Shield*, int n) {
	if (n != -1)
		return grabShield(n);
	else
		return grabShield();
}

void Room::lootEnemies(array<short, 4>* loot_list) {
	for (forward_list<Enemy*>::iterator i = _enemy_list->begin(); i != _enemy_list->end(); i++) {
		if ((*i)->isBoss()) {

			Boss* b = (Boss*) & *(*i);
			Sword* sword = b->getSword();
			Shield* shield = b->getShield();
			b->getLoot(loot_list);
			if (sword)
				addItem(sword);
			if (shield)
				addItem(shield);
		}
		else
			(*i)->getLoot(loot_list);
	}
	_enemy_list = NULL;
	throw Dungeon_Exception("Se han looteado los enemigos");
}

void Room::setIsLooteable() {
	
	_isLooteable = true;
}

bool Room::isLooteable() {
	return _isLooteable;
}

bool Room::generateEnemies(short roomsPassed) {
	if (_roomsForEnemy > 0 && (roomsPassed % _roomsForEnemy) == 0) {
		_enemy_list = new forward_list<Enemy* >;
		_enemy_list->push_front(new Enemy(30,23,8,7,12,20,1,2,3,0));
		_enemy_list->push_front(new Enemy(30,12,13,21,7,17,3,3,3,3));
		_enemy_list->push_front(new Enemy(30,5,22,11,7,20,1,3,1,0));
		return true;
	}
	else  if (_roomsForEnemy < 0) {
		int i = abs(_roomsForEnemy);
		int r;
		srand(time(NULL));
		r = rand() % i + 1;
		if (r == 1) {
			_enemy_list = NULL;
			_enemy_list = new forward_list<Enemy*>;
			_enemy_list->push_front(new Enemy(20, 10, 3, 10, 5, 20, 1,1,0,0));
			_enemy_list->push_front(new Enemy(25, 5, 5, 15, 9, 15 ,2,2,2,0));
			_enemy_list->push_front(new Enemy(15, 7, 7, 15, 5, 5, 1,1,1,0));
		}
	} else
		return false;
	
}

RoomSaver Room::getRoomSaver() {
	RoomSaver room_saver;
	room_saver.id = _id;
	if (hasEnemy())
		room_saver.hasEnemy = true;
	else
		room_saver.hasEnemy = false;
	for (int i = 0; i < _item_list.size(); i++) {
		room_saver.item_id_list.push_back(_item_list[i]->getID());
	}
	return room_saver;
}

int Room::getID() {
	return _id;
}

