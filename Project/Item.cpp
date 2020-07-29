#include "Item.h"
#include "Player.h"

#include <iostream>

extern Player* player;

using std::cout;
using std::endl;

Item::Item()
{
	name = "Unnamed Item";
	value = 0;
}

Item::Item(string name, int value)
{
	this->name = name;
	this->value = value;
}

Item::~Item()
{
}

void Item::Use()
{
	player->health += value;
	cout << name << " is in this room." << endl;
	cout << "You now have " << player->health << " health." << endl;
	RemoveFromRoom();
}

void Item::Activate()
{
	Use();
}
