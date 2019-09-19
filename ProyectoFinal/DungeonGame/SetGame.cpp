#include <fstream>
#include <stdio.h>
#include "SetGame.h"


using std::ofstream;
using std::ifstream;

SetGame::SetGame(vector<Room>* room_list, Player* player, vector<Sword>* sword_list, vector<Shield>* shield_list, vector<Key>* key_list, array<bool, 28>* rooms_visited) :
	_room_list(room_list), _player(player), _sword_list(sword_list), _shield_list(shield_list), _key_list(key_list), _rooms_visited(rooms_visited)
{

}

void SetGame::setRooms() {
	_room_list->push_back(Room("Cuarto 0", false, 1, 0));
	_room_list->push_back(Room("Cuarto 1", false, 2, 0));
	_room_list->push_back(Room("Cuarto 2", false, 3, 0));
	_room_list->push_back(Room("Cuarto 3", true, 4, 0));
	_room_list->push_back(Room("Cuarto 4", false, 5, 0));
	_room_list->push_back(Room("Cuarto 5", false, 6, 0));
	_room_list->push_back(Room("Cuarto 6", false, 7, 0));
	_room_list->push_back(Room("Cuarto 7", false, 8, 0));
	_room_list->push_back(Room("Cuarto 8", true, 9, 0));
	_room_list->push_back(Room("Cuarto 9", false, 10, 0));

	_room_list->push_back(Room("Cuarto 10", false, 11, 0));
	_room_list->push_back(Room("Cuarto 11", false, 12, 5));
	_room_list->push_back(Room("Cuarto 12", false, 13, 10));
	_room_list->push_back(Room("Cuarto 13", false, 14, 0));
	_room_list->push_back(Room("Cuarto 14", false, 15, 0));
	_room_list->push_back(Room("Cuarto 15", false, 16, 0));
	_room_list->push_back(Room("Cuarto 16", false, 17, 0));
	_room_list->push_back(Room("Cuarto 17", false, 18, 0));
	_room_list->push_back(Room("Cuarto 18", false, 19, 0));
	_room_list->push_back(Room("Cuarto 19", false, 20, 0));

	_room_list->push_back(Room("Cuarto 20", false, 21, 0));
	_room_list->push_back(Room("Cuarto 21", false, 22, 0));
	_room_list->push_back(Room("Cuarto 22", false, 23, 0));
	_room_list->push_back(Room("Cuarto 23", false, 24, 0));
	_room_list->push_back(Room("Cuarto 24", false, 25, 0));
	_room_list->push_back(Room("Cuarto 25", false, 26, 0));
	_room_list->push_back(Room("Cuarto 26", false, 27, 0));
	_room_list->push_back(Room("Cuarto 27", false, 28, 0));
}

void SetGame::setDoorList() {
	vector<Door*> door_list;
	door_list.push_back(new Door(&_room_list->at(0), &_room_list->at(3), 0, false));
	door_list.push_back(new Door(&_room_list->at(2), &_room_list->at(3), 1, false));
	door_list.push_back(new Door(&_room_list->at(3), &_room_list->at(4), 2, false));
	door_list.push_back(new Door(&_room_list->at(4), &_room_list->at(5), 3, false));
	door_list.push_back(new Door(&_room_list->at(1), &_room_list->at(6), 4, false));
	door_list.push_back(new Door(&_room_list->at(2), &_room_list->at(7), 5, false));
	door_list.push_back(new Door(&_room_list->at(3), &_room_list->at(8), 6, false));
	door_list.push_back(new Door(&_room_list->at(4), &_room_list->at(12), 7, false));
	door_list.push_back(new Door(&_room_list->at(6), &_room_list->at(10), 8, false));
	door_list.push_back(new Door(&_room_list->at(9), &_room_list->at(11), 9, false));
	door_list.push_back(new Door(&_room_list->at(7), &_room_list->at(13), 10, false));
	door_list.push_back(new Door(&_room_list->at(10), &_room_list->at(11), 11, false));
	door_list.push_back(new Door(&_room_list->at(11), &_room_list->at(12), 12, false));
	door_list.push_back(new Door(&_room_list->at(12), &_room_list->at(13), 13, false));
	door_list.push_back(new Door(&_room_list->at(10), &_room_list->at(14), 14, false));
	door_list.push_back(new Door(&_room_list->at(11), &_room_list->at(16), 15, false));
	door_list.push_back(new Door(&_room_list->at(13), &_room_list->at(17), 16, false));
	door_list.push_back(new Door(&_room_list->at(14), &_room_list->at(15), 17, false));
	door_list.push_back(new Door(&_room_list->at(15), &_room_list->at(16), 18, false));
	door_list.push_back(new Door(&_room_list->at(16), &_room_list->at(12), 19, false));
	door_list.push_back(new Door(&_room_list->at(17), &_room_list->at(0), 20, false));
	door_list.push_back(new Door(&_room_list->at(14), &_room_list->at(18), 21, false));
	door_list.push_back(new Door(&_room_list->at(15), &_room_list->at(19), 22, false));
	door_list.push_back(new Door(&_room_list->at(16), &_room_list->at(20), 23, false));
	door_list.push_back(new Door(&_room_list->at(13), &_room_list->at(21), 24, false));
	door_list.push_back(new Door(&_room_list->at(17), &_room_list->at(21), 25, false));
	door_list.push_back(new Door(&_room_list->at(21), &_room_list->at(22), 26, false));
	door_list.push_back(new Door(&_room_list->at(18), &_room_list->at(23), 27, false));
	door_list.push_back(new Door(&_room_list->at(19), &_room_list->at(25), 28, false));
	door_list.push_back(new Door(&_room_list->at(20), &_room_list->at(25), 29, false));
	door_list.push_back(new Door(&_room_list->at(21), &_room_list->at(27), 30, false));
	door_list.push_back(new Door(&_room_list->at(24), &_room_list->at(27), 31, false));
	door_list.push_back(new Door(&_room_list->at(25), &_room_list->at(26), 32, false));
	door_list.push_back(new Door(&_room_list->at(26), &_room_list->at(27), 33, false));
	door_list.push_back(new Door(&_room_list->at(7), &_room_list->at(8), 34, false));

	for (int i = 0; i < door_list.size(); i++) {
		Room* r;
		r = door_list[i]->getNextRoom();
		r->addDoor(door_list[i]);
		r = door_list[i]->getPreviousRoom();
		r->addDoor(door_list[i]);
	}
}

void SetGame::setItems() {
	_sword_list->push_back(Sword(50, "Espada I", 3, 2, 1, 0, 0));
	_sword_list->push_back(Sword(51, "Espada II", 6, 5, 2, 2, 0));
	_sword_list->push_back(Sword(52, "Espada III", 16, 10, 5, 5, -3));
	_sword_list->push_back(Sword(53, "Katana I", 2, 0, 3, 1, 0));
	_sword_list->push_back(Sword(54, "Katana II", 6, 0, 5, 0, 4));
	_sword_list->push_back(Sword(55, "Katana III", 12, 0, 7, 7, 7));
	_sword_list->push_back(Sword(56, "Scimitarra I", 1, 2, 0, 3, 0));
	_sword_list->push_back(Sword(57, "Scimitarra II", 5, 3, 3, 2, 2));
	_sword_list->push_back(Sword(58, "Scimitarra III", 7, 7, 7, 7, 5));
	_sword_list->push_back(Sword(59, "Guadaña I", 2, 3, 1, 0, 0));
	_sword_list->push_back(Sword(60, "Guadaña II", 5, 6, 0, 4, 0));
	_sword_list->push_back(Sword(61, "Guadaña III", 10, 16, 3, 3, 0));
	_sword_list->push_back(Sword(62, "Excalibur", 20, 15, -2, -2, 4));

	_shield_list->push_back(Shield(65, "Escudo de Madera I", 3, 2, 1));
	_shield_list->push_back(Shield(66, "Escudo de Madera II", 6, 5, 4));
	_shield_list->push_back(Shield(67, "Escudo de Madera III", 12, 11, 10));
	_shield_list->push_back(Shield(68, "Escudo de Metal I", 1, 3, 2));
	_shield_list->push_back(Shield(69, "Escudo de Metal II", 4, 5, 6));
	_shield_list->push_back(Shield(70, "Escudo de Metal III", 10, 12, 11));
	_shield_list->push_back(Shield(71, "Escudo pequeño I", 2, 1, 3));
	_shield_list->push_back(Shield(72, "Escudo pequeño II", 4, 5, 6));
	_shield_list->push_back(Shield(73, "Escudo pequeño III", 11, 10, 12));

	_key_list->push_back(Key(4, "Llave de boss"));//0
	_key_list->push_back(Key(7, ""));//1
	_key_list->push_back(Key(9, ""));//2
	_key_list->push_back(Key(10, "Llave de boss"));//3
	_key_list->push_back(Key(14, ""));//4
	_key_list->push_back(Key(15, ""));//5
	_key_list->push_back(Key(20, ""));//6
	_key_list->push_back(Key(27, "Llave de boss"));//7
	_key_list->push_back(Key(28, ""));//8
	_key_list->push_back(Key(33, "Llave de boss"));//9
}

void SetGame::loadGame() {
	setRooms();
	setDoorList();
	setItems();

	ifstream savedFile;
	savedFile.open("DungeonGame.dat", std::ios::in);
	if (!savedFile.fail()) {
		PlayerSaver s;
		RoomSaver r;
		int num;
		short size;
		for (int i = 0; i < 28; i++) {
			savedFile.read((char*)& _rooms_visited[i], sizeof(bool));
		}
		savedFile.read((char*)& s.room_id, sizeof(int));
		savedFile.read((char*)& s.sword, sizeof(int));
		savedFile.read((char*)& s.shield, sizeof(int));
		savedFile.read((char*)& s.life, sizeof(int));
		savedFile.read((char*)& s.rooms_passed, sizeof(int));
		savedFile.read((char*)& s.mana, sizeof(int));
		savedFile.read((char*)& s.bosses_defeated, sizeof(short));
		savedFile.read((char*)& size, sizeof(short));
		for (int i = 0; i < size; i++) {
			savedFile.read((char*)& num, sizeof(int));
			s.key_list.push_back(num);
		}
		for (int i = 0; i < 4; i++) {
			savedFile.read((char*)& num, sizeof(int));
			s.loot_list[i] = num;
		}
		loadPlayer(s);
		savedFile.read((char*)& r.id, sizeof(int));
		savedFile.read((char*)& r.hasEnemy, sizeof(bool));
		savedFile.read((char*)& size, sizeof(short));
		while (!savedFile.eof()) {
			if (r.hasEnemy)
				fillEnemyRoom(r.id - 1);
			if (size > 0) {
				vector<int> item;
				for (int i = 0; i < size; i++) {
					savedFile.read((char*)& num, sizeof(int));
					item.push_back(num);
				}
				fillRoom(r.id - 1, item);

			}
			savedFile.read((char*)& r.id, sizeof(int));
			savedFile.read((char*)& r.hasEnemy, sizeof(bool));
			savedFile.read((char*)& size, sizeof(short));
		}
		int i = 1;
	}
	else {
		_rooms_visited->fill(false);
		*_rooms_visited->begin() = true;
		fillRoom();
		fillEnemyRoom();
		loadPlayer();

	}
	savedFile.close();
}

void SetGame::fillEnemyRoom(int id) {
	switch (id) {
	case 3:
		_room_list->at(3).addEnemy(new Enemy(1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
		break;
	case 8:
		_room_list->at(8).addEnemy(new Enemy(1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
		_room_list->at(8).addEnemy(new Boss(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, NULL, NULL));
		break;
	}
}

void SetGame::fillEnemyRoom() {
	_room_list->at(3).addEnemy(new Enemy(1, 1, 1, 1, 1, 1, 1, 1, 1, 1));

	_room_list->at(8).addEnemy(new Enemy(1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
	_room_list->at(8).addEnemy(new Boss(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, NULL, NULL));
}

void SetGame::fillRoom() {
	_room_list->at(0).addItem(&_sword_list->at(0));
	_room_list->at(0).addItem(&_sword_list->at(1));

	//0

	//1

	//2

	//3

	//4

	//5
	_room_list->at(5).addItem(&_key_list->at(2));
	//6
	_room_list->at(6).addItem(&_key_list->at(9));
	//7
	_room_list->at(7).addItem(&_key_list->at(1));
	//8

	//9

	//10

	//11
	_room_list->at(11).addItem(&_key_list->at(6));
	//12
	_room_list->at(12).addItem(&_key_list->at(8));
	_room_list->at(12).addItem(&_key_list->at(4));
	//13

	//14

	//15

	//16

	//17
	_room_list->at(17).addItem(&_key_list->at(7));
	//18

	//19
	_room_list->at(19).addItem(&_key_list->at(5));
	//20

	//21

	//22
	_room_list->at(22).addItem(&_key_list->at(0));
	//23

	//24

	//25
	_room_list->at(25).addItem(&_key_list->at(3));
	//26

	//27
}

void SetGame::fillRoom(int id, vector<int> item_list) {
	for (int i = 0; i < item_list.size(); i++) {
		if (item_list[i] >= 50 && id < 65) {
			_room_list->at(id).addItem(&_sword_list->at(item_list[i] % 50));
		}
		else if (item_list[i] >= 65) {
			_room_list->at(id).addItem(&_shield_list->at(item_list[i] % 65));
		}
		else {
			_room_list->at(id).addItem(getKey(item_list[i]));
		}
	}
}

void SetGame::loadPlayer(PlayerSaver p) {
	_player->setCurrentRoom(&_room_list->at(p.room_id - 1));
	if (p.sword != -1)
		_player->setSword(&_sword_list->at(p.sword % 50));
	if (p.shield != -1)
		_player->setShield(&_shield_list->at(p.shield % 65));
	for (int i = 0; i < p.key_list.size(); i++) {
		_player->addKey(getKey(p.key_list[i]));
	}
	_player->setValues(p);
}

void SetGame::loadPlayer() {
	_player->setCurrentRoom(&_room_list->at(0));
}

Key* SetGame::getKey(int i) {
	switch (i) {
	case 4: return &_key_list->at(0);
		break;
	case 7: return &_key_list->at(1);
		break;
	case 9: return &_key_list->at(2);
		break;
	case 10: return &_key_list->at(3);
		break;
	case 14: return &_key_list->at(4);
		break;
	case 15: return &_key_list->at(5);
		break;
	case 20: return &_key_list->at(6);
		break;
	case 27: return &_key_list->at(7);
		break;
	case 28: return &_key_list->at(8);
		break;
	case 33: return &_key_list->at(9);
		break;

	}
}