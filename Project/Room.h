#pragma once
#include "Spawnable.h"

class Room
{
public:
	Room();
	~Room();

	Spawnable* ObjectSpawned;
	void OnRoomEntered();
};

extern Room Rooms[6][6];
