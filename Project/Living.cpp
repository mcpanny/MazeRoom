#include "Living.h"
#include "xorshift.h"
#include "Room.h"

#include <windows.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

Living::Living()
{
	enemy = nullptr;
}

Living::~Living()
{
}

bool Living::IsAlive()
{
	return health > 0;
}

void Living::Attack()
{
	// if the living instances are alive
	// allow a fight
	if (IsAlive() && enemy->IsAlive())
	{
		Fight();
		enemy->Attack();
	}
}

void Living::Fight()
{
	// if the player is not alive, 
	// don't run the rest of the code
	if (!IsAlive())
	{
		cout << "You have died." << endl;
		return;
	}

	cout << name << " damages " << enemy->name << " by " << attackDamage << endl;
	attackDamage += random() % 11;
	enemy->health -= attackDamage;

	if (enemy->health < 0)
	{
		enemy->health = 0;
	}

	cout << enemy->name << ": " << enemy->health << " health remaining." << endl;
	Sleep(500); // delay
}