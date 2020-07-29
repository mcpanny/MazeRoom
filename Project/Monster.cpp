#include "Monster.h"
#include "xorshift.h"
#include "Room.h"

#include <iostream>

using std::cout;
using std::endl;

Monster::Monster()
{
	name = "Monster";
	health = 30;
	attackDamage = 5;
}

Monster::~Monster()
{
}

void Monster::Heal()
{
	health += random() % 11;
	cout << name << " heals itself." << endl;
	cout << name << ": " << health << " health remaining." << endl;
}

void Monster::Activate()
{
		cout << name << " is in this room." << endl;
		cout << "Press k to fight the monster. Press l to try to run away." << endl;
}

void Monster::Attack()
{
	if (!IsAlive())
	{
		cout << "You defeated the monster!" << endl;
		RemoveFromRoom();
		return;
	}

	int action = random() % 16;
	if (action <= 10)
	{
		Fight();
	}
	else
	{
		Heal();
	}
}