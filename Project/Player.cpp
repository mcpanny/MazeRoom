#include "xorshift.h"
#include "Player.h"
#include "Living.h"
#include "Room.h"
#include "GameEnded.h"

#include "Monster.h"

#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;

extern void saveGame();
extern void loadGame();

Player::Player()
{
	health = 100;
	attackDamage = 5;
}

Player::~Player()
{
}

void Player::Move(Direction direction)
{
	switch (direction)
	{
	case NORTH:
	{
		x++;
		break;
	}
	case SOUTH:
	{
		x--;
		break;
	}
	case EAST:
	{
		y--;
		break;
	}
	case WEST:
	{
		y++;
		break;
	}
	}

	// prevent player from moving outside the room
	// take the smaller value of x or y if it is less than 5
	x = std::min(x, 5);
	y = std::min(y, 5);
	
	// take the larger value of x or y if it is more than 0
	x = std::max(x, 0);
	y = std::max(y, 0);

	// activate the instances when the player enters a room
	// that has an object
	Rooms[x][y].OnRoomEntered();

	// if the object that is spawned is a monster,
	// assign the enemy to the type casted value for the monster
	// and assign the player as the enemy for the enemy
	if (Rooms[x][y].ObjectSpawned && Rooms[x][y].ObjectSpawned->name == "Monster")
	{
		enemy = (Living*)Rooms[x][y].ObjectSpawned;
		enemy->enemy = this;
	}
	else
	{
		enemy = nullptr;
	}
}

void Player::OnCommand(const char c)
{
	// if there is an enemy
	// the player should only be allowed to enter k or l
	if (enemy)
	{
		switch (c)
		{
			case 'k':
			{
				Attack();
				if (!enemy->IsAlive())
				{
					enemy = nullptr;
				}
				break;
			}
			case 'l':
			{
				Flee();
				break;
			}
			default:
			{
				cout << "Invalid command. Try again. Press k to fight. Press l to try to run away." << endl;
			}
		}
	}
	else
	{
		switch (c)
		{
			case 'w':
			{
				Move(NORTH);
				break;
			}
			case 's':
			{
				Move(SOUTH);
				break;
			}
			case 'a':
			{
				Move(EAST);
				break;
			}
			case 'd':
			{
				Move(WEST);
				break;
			}
			case 'p':
			{
				// save the file and close the game
				gameEnded = true;
				saveGame();
				break;
			}
			case 'o':
			{
				loadGame();
				break;
			}
			default:
			{
				cout << "Invalid command. Try again." << endl;
			}
		}
	}
}

void Player::Flee()
{
	int action = random() % 8;
	if (action <= 5)
	{
		cout << "You have successfully ran away." << endl;
		enemy = nullptr;
	}
	else
	{
		cout << "You failed to run away. The enemy attacks..." << endl;
		enemy->Fight();
	}
}