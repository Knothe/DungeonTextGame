#include "pch.h"
#include <utility>
#include <limits.h>
#include <time.h>
#include "Dungeon_Battle.h"

extern "C" DUNGEON_BATTLE_API bool isAvoidedStrong(const short speed1, const short speed2) {
	short r;
	srand(time(NULL));
	r = rand() % (17 + speed1)+ 1;
	if (r > speed2) 
		return false;
	else
		return true;
}

extern "C" DUNGEON_BATTLE_API bool isAvoidedWeak(const short speed1, const short speed2) {
	short r;
	srand(time(NULL));
	r = rand() % (30 + speed1) + 1;
	if (r > speed2)
		return false;
	else
		return true;
}

extern "C" DUNGEON_BATTLE_API short getDamageStrong(const short attack, const short defense) {
	short d;
	d = attack * 2;
	d -= defense * .5f;
	if (d < 0) 
		return 0;
	
	return d;
}

extern "C" DUNGEON_BATTLE_API short getDamageWeak(const short attack, const short defense) {
	short d;
	d = attack * .9f;
	d -= defense * .5f;
	if (d < 0)
		return 0;
	return d;
}

extern "C" DUNGEON_BATTLE_API short getMagicDamage(const short attack, const short defense) {
	short d;
	d = attack * .75f;
	d -= defense * .5f;
	if (d < 0)
		return 0;
	return d;
}