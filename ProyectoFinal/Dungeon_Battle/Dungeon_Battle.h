#pragma once

#ifdef DUNGEON_BATTLE_EXPORTS
#define DUNGEON_BATTLE_API _declspec(dllexport)
#else
#define DUNGEON_BATTLE_API _declspec(dllexport)
#endif 

extern "C" DUNGEON_BATTLE_API bool isAvoidedStrong(const short speed1, const short speed2);

extern "C" DUNGEON_BATTLE_API bool isAvoidedWeak(const short speed1, const short speed2);

extern "C" DUNGEON_BATTLE_API short getDamageStrong(const short attack, const short defense);

extern "C" DUNGEON_BATTLE_API short getDamageWeak(const short attack, const short defense);

extern "C" DUNGEON_BATTLE_API short getMagicDamage(const short attack, const short defense);


