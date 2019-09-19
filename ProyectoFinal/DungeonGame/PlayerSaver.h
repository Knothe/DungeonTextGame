#pragma once
#include <vector>
#include <array>

using std::vector;
using std::array;

struct PlayerSaver {
	int room_id;
	int sword;
	int shield;
	vector<int> key_list;
	int life;
	int rooms_passed;
	int mana;
	short bosses_defeated;
	array<short, 4> loot_list;

	void operator=(PlayerSaver other){
		room_id = other.room_id;
		sword = other.sword;
		shield = other.shield;
		key_list = other.key_list;
		life = other.life;
		rooms_passed = other.rooms_passed;
		mana = other.mana;
		bosses_defeated = other.bosses_defeated;
		for (int i = 0; i < 4; i++)
			loot_list[i] = other.loot_list[i];
	}
};