#pragma once

#include "Living.h"

// types for player movement
enum Direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

class Player : public Living
{
public:
	Player();
	~Player();

	void Move(Direction);
	void OnCommand(const char);
	void Flee();
};

