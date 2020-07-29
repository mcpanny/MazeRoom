#include "Room.h"

#include <iostream>

Room Rooms[6][6]; // 2D array

Room::Room()
{
	ObjectSpawned = nullptr;
}


Room::~Room()
{
}

void Room::OnRoomEntered()
{
	if (ObjectSpawned && 
		ObjectSpawned->name != "Monster" && 
		ObjectSpawned->name != "Poison" &&
		ObjectSpawned->name != "Potion" &&
		ObjectSpawned->name != "Castle")
	{
		std::cout << "You are back at your starting point." << std::endl;
	}
	else if (ObjectSpawned)
	{
		ObjectSpawned->Activate();
	}
	else
	{
		std::cout << "There is nothing here." << std::endl;
	}
}
