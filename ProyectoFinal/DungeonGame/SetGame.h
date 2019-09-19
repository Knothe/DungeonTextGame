#pragma once
#include "Sword.h"
#include "Shield.h"
#include "Key.h"
#include "Boss.h"
#include "Enemy.h"
#include "Room.h"
#include "Player.h"
#include "PlayerSaver.h"
#include "RoomSaver.h"
#include <array>


class SetGame
{
private:
	vector<Room>* _room_list;
	Player* _player;
	vector<Sword>* _sword_list;
	vector<Shield>* _shield_list;
	vector<Key>* _key_list;
	array<bool, 28>* _rooms_visited;
public:
	SetGame(vector<Room>*, Player*, vector<Sword>*, vector<Shield>*, vector<Key>*, array<bool, 28>*);
	void setRooms();
	void setDoorList();
	void setItems();
	void loadGame();
	void loadPlayer(PlayerSaver p);
	void loadPlayer();
	Key* getKey(int i);
	void fillRoom(int, vector<int>);
	void fillRoom();
	void fillEnemyRoom(int id);
	void fillEnemyRoom();
};

