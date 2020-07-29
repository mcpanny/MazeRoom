#include "Player.h"
#include "GameEnded.h"
#include "Monster.h"
#include "Item.h"
#include "Spawnable.h"
#include "Room.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::getline;
using std::stoi;

void startGame();
void saveGame();
void instructions();
void loadGame();

Player* player;
Spawnable* castle;
Monster* monster[5];
Item* potion[5];
Item* poison[5];

int main()
{
	instructions();
	startGame();

	return 0;
}

void instructions()
{
	cout << "\nFind your way to the castle without dying." << endl;
	cout << "Keys"
		<< "\n" << "w: North (up)"
		<< "\n" << "s: South (down)"
		<< "\n" << "a: East (left)"
		<< "\n" << "d: West (right)"
		<< "\n" << "k: Fight"
		<< "\n" << "l: Flee"
		<< "\n" << "p: Save and quit the game"
		<< "\n" << "o: Load game"
	    << "\n" << "==============================\n" << endl;
}

void startGame()
{
	// spawn the instances
	player = new Player();
	castle = new Spawnable();
	castle->name = "Castle";

	for (int i = 0; i < 5; i++)
	{
		monster[i] = new Monster();
		potion[i] = new Item("Potion", 10);
		poison[i] = new Item("Poison", -10);
	}

	// player allowed to move
	player->RemoveFromRoom();

	/*
	cout << castle->x << "," << castle->y << "..." << castle->name << endl;

	for (int i = 0; i < 4; i++)
	{
		cout << monster[i]->x << "," << monster[i]->y << "..." << monster[i]->name << endl;
	}

	for (int i = 0; i < 4; i++)
	{
		cout << potion[i]->x << "," << potion[i]->y << "..." << potion[i]->name << endl;
	}

	for (int i = 0; i < 4; i++)
	{
		cout << poison[i]->x << "," << poison[i]->y << "..." << poison[i]->name << endl;
	}
	*/

	string name;
	cout << "Enter name:" << endl;
	cin >> name;
	player->name = name;

	// loop while player tries to find the castle
	while (!gameEnded)
	{
		cout << "Player coordinates: (" << player->x << "," << player->y << ")" << endl;
		cout << "Player health: " << player->health << endl;
		cout << "Enter commands:" << endl;

		string command;
		char c;
		cin >> command;

		if (command.length() >= 1)
		{
			c = command.at(0);
			player->OnCommand(c);
		}
		else
		{
			cout << "You did not enter a command." << endl;
		}

		cout << "================================================" << endl;
	}
}

void saveGame()
{
	// all instances that are spawned and not null
	// will be saved to a file
	ofstream saveFile;
	saveFile.open("saveFile.txt", std::ios_base::out);
	player->Dump(saveFile);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (Rooms[i][j].ObjectSpawned)
			{
				Rooms[i][j].ObjectSpawned->Dump(saveFile);
			}
		}
	}
	saveFile.close();
}

void loadGame()
{
	// remove all the members of the instances that spawned
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (Rooms[i][j].ObjectSpawned)
			{
				Rooms[i][j].ObjectSpawned->RemoveFromRoom();
			}
		}
	}

	int numMonsters = 0;
	int numPotions = 0;
	int numPoison = 0;

	ifstream loadFile;
	loadFile.open("saveFile.txt", std::ios_base::in);

	// get the player information and location
	string name;
	string xPosition;
	string yPosition;
	getline(loadFile, name, ',');
	getline(loadFile, xPosition, ',');
	getline(loadFile, yPosition);

	// stoi - string to integer
	int x = stoi(xPosition);
	int y = stoi(yPosition);

	player->name = name;
	player->MoveTo(x, y);
	player->RemoveFromRoom();

	while (loadFile.good())
	{
		// load all other instances that were stored in text file
		getline(loadFile, name, ',');
		getline(loadFile, xPosition, ',');
		getline(loadFile, yPosition);

		if (!name.empty())
		{
			x = stoi(xPosition);
			y = stoi(yPosition);

			if (name == "Monster")
			{
				monster[numMonsters]->MoveTo(x, y);
				numMonsters++;
			}

			else if (name == "Potion")
			{
				potion[numPotions]->MoveTo(x, y);
				numPotions++;
			}

			else if (name == "Poison")
			{
				poison[numPoison]->MoveTo(x, y);
				numPoison++;
			}

			else if (name == "Castle")
			{
				castle->MoveTo(x, y);
			}
		}
	}
	
	loadFile.close();
}