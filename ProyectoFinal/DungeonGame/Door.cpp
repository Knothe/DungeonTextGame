#include "Door.h"

/*
@param p & n : pointers to connecting rooms
@param i : door's id
*/
Door::Door(Room* p, Room* n, int i, bool is_closed) : _previous(p), _next(n), _id(i), _is_closed(is_closed) {}

Door::Door() {
	_id = 0;
}

/*
@param r: current room
*/
Room* Door::getNextDoor(Room* const r) {
	if (r != _previous) {
		return _previous;
	} else {
		return _next;
	}
}

/*
@return el id de la puerta
*/
int Door::getId() {
	return _id;
}

bool Door::isClosed()

{
	return _is_closed;
}

Room* Door::getNextRoom() {
	return _next;
}

Room* Door::getPreviousRoom() {
	return _previous;
}