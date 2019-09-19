#ifndef ROOM
#define ROOM

#include "Door.h"
#include <vector>
#include <array>
#include <forward_list>
#include "Key.h"
#include "Shield.h"
#include "Sword.h"
#include "Enemy.h"
#include "Boss.h"
#include "Dungeon_Exception.h"
#include "RoomSaver.h"

using std::forward_list;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::array;
using std::to_string;

class Door;

class Room
{
private:

	short _roomsForEnemy;
	short _id;
	forward_list<Door*> _door_list;
	forward_list<Enemy* >* _enemy_list;
	vector<Item *> _item_list;
	string _text;
	bool _isLooteable = false;

public:
	Room(std::string text, bool, short, short);
	int getID();
	void addDoor(Door*);
	void addEnemy(Enemy*);
	void addItem(Item*);
	string getData();
	Door* getDoor(int, bool, int);
	Sword* grabSword(int);
	Shield* grabShield(int);
	Key* grabKey(int);
	Sword* grabSword();
	Shield* grabShield();
	Key* grabKey();
	bool hasBoss();
	bool hasEnemy();
	string printEnemies();
	forward_list<Enemy*>* getEnemyList();
	void lootEnemies(array<short, 4>*);
	void setIsLooteable();
	bool isLooteable();
	Sword* getItem(Sword*, int);
	Shield* getItem(Shield*, int);
	bool generateEnemies(short);
	RoomSaver getRoomSaver();
};

#endif