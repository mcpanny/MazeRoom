#include "Spawnable.h"
#include "Room.h"
#include "xorshift.h"
#include "GameEnded.h"

#include <iostream>

using std::cout;
using std::endl;

Spawnable::Spawnable()
{
	// assign x,y from 0-5
	// repeat if x,y is taken (objectSpawned)
	do
	{
		x = random() % 6;
		y = random() % 6;
	} while (Rooms[x][y].ObjectSpawned);

	Rooms[x][y].ObjectSpawned = this;
}


Spawnable::~Spawnable()
{
}

void Spawnable::Dump(ofstream& saveFile)
{
	// write player name and location to file
	saveFile << name << "," << x << "," << y << endl;
}

void Spawnable::Activate()
{
	if (Rooms[x][y].ObjectSpawned->name == "Castle")
	{
		cout << "You found the castle!" << endl;
		gameEnded = true;
	}
}

void Spawnable::RemoveFromRoom()
{
	// reset the room
	Rooms[x][y].ObjectSpawned = nullptr;
}

void Spawnable::MoveTo(int x, int y)
{
	// this will be used to transfer the x,y from a file
	// and store it into the instances
	this->x = x;
	this->y = y;
	Rooms[x][y].ObjectSpawned = this;
}
