#pragma once
#include <vector>

using std::vector;

struct RoomSaver {
	int id;
	bool hasEnemy;
	vector<int> item_id_list;
	void operator=(RoomSaver other) {
		id = other.id;
		hasEnemy = other.hasEnemy;
		item_id_list = other.item_id_list;
	}
};