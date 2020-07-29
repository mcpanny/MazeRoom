#pragma once
#include "Spawnable.h"

class Item : public Spawnable
{
public:
	Item();
	Item(string name, int value);

	~Item();

	int value;

	void Use();

	virtual void Activate();
};

