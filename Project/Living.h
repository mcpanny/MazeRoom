#pragma once

#include "Spawnable.h"

class Living : public Spawnable
{
public:
	Living();
	~Living();

	Living* enemy;

	int health;
	int attackDamage;

	void Fight();
	bool IsAlive();

	virtual void Attack();
};

