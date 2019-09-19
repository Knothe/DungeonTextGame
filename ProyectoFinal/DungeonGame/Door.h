#ifndef DOOR
#define DOOR

#include "Room.h"

class Room;

class Door
{
private:
	int _id;
	Room* _next;
	Room* _previous;
	bool _is_closed;

public:
	Door();
	Door(Room*, Room*, int, bool);
	Room* getNextDoor(Room* const);
	Room* getNextRoom();
	Room* getPreviousRoom();
	int getId();	
	bool isClosed();

};

#endif