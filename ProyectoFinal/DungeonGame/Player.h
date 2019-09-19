#pragma once
#include <windows.h>
#include "Key.h"
#include "Shield.h"
#include "Sword.h"
#include <vector>
#include <map>
#include <array>
#include <string>
#include "Room.h"
#include "Dungeon_Exception.h"
#include "PlayerSaver.h"

using std::vector;
using std::map;
using std::string;
using std::array;
using std::pair;
using std::to_string;

class Player
{
private:
	HWND _hWnd;
	vector<Key*> _key_list;
	Shield* _shield;
	Sword* _sword;
	Room* _current_room;
	array<short, 8> _magic_list;
	bool _isInBattle = false;
	int _life;
	unsigned int _attack;
	unsigned int _defense;
	unsigned int _speed;
	unsigned int _magic_attack;
	unsigned int _magic_defense;
	unsigned int _mana = 100;
	short _rooms_passed = 0;
	array<short, 4> _loot_list;
	short _bosses_defeated = 0;
	bool _isPlayerTurn = false;
	map<string, short> _indication_list;
	vector<map<string, short>> _action_list;

	void _magicAttack0(forward_list<Enemy*>*);
	void _magicAttack1(forward_list<Enemy*>*);
	void _magicAttack2();
	void _magicAttack3();
	void _magicAttack4();
	void _magicAttack5();
	void _magicAttack6();
	void _magicAttack7(forward_list<Enemy*>*);
	void _craftearItem(int);
	void _verIndicaciones();
	void _magicAttack(int n);
	void _setIndicationList();
	
	void applyAction(short, short);
	int findInMap(map<string, short>* const, string);
	void changeRoom(int);
	void grabKey(int);
	void printItems();
	void leaveKey(int);
	void printStatus();
	void printMagic();
	template<class T>
	T* grabItem(T*, int);
	template<class T>
	void leaveItem(T*);
	void lootEnemies();
	void attackBoss(forward_list<Enemy*>* const enemy_list, bool p);
	void attackMinion(forward_list<Enemy*>* const enemy_list, bool);
	void attackEnemy(forward_list<Enemy*>* const enemy_list, bool);
	template<class T>
	void attackAnyone(T*, bool);
	template<class T>
	void enemyAttack(T*, int);
	int getAttack();
	int getDefense();
	int getSpeed();
	int getMagicAttack();
	int getMagicDefense();
	short getBossesDefeated();
	void checkCrafteable();
	void startBattle();
	void _displayHelpText();
	

public:
	Player(int, int, int, int, int, int, Room*);
	Player();
	Player(Room* current_room);
	Room* getCurrentRoom();
	void readIndication(string indication);
	void setPlayerTurn(bool);
	void setIsInBattle(bool);
	void reduceSpells();
	void setHWND(HWND);
	void setCurrentRoom(Room* current_room);
	bool isInBattle();
	bool isTurn();
	void setSword(Sword*);
	void enemyTurn(forward_list<Enemy*>*);
	void endBattle();
	void restartPlayer(Room*);
	void setShield(Shield*);
	void addKey(Key*);
	void setValues(PlayerSaver);
	PlayerSaver getPlayerSaver();
};

