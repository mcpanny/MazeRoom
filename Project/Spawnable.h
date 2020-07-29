#pragma once

#include <string>
#include <fstream>

using std::string;
using std::ofstream;

class Spawnable
{
public:
	Spawnable();
	~Spawnable();

	int x;
	int y;
	string name;

	void Dump(ofstream& saveFile);
	void RemoveFromRoom();
	void MoveTo(int x, int y);

	virtual void Activate();
};