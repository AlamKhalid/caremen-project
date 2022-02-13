#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "Map.h"

class Game {
private:
	// to store map in game
	Map map;
	// other necessary variables
	int serverRoom = 1, numNPC, numHackers;
public:
	void initMap();
	void displayOtherMoves(bool dh);
	void checkMisfortune();
	void browseStackoverflow();
	void nextRoom();
	void playGame();
};
#endif