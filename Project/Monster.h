#pragma once
#include "Living.h"

class Monster : public Living
{
public:
	Monster();
	~Monster();

	virtual void Attack() override;
	virtual void Activate();
	void Heal();
};

