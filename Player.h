#ifndef PLAYER_H
#define PLAYER_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// player class, it store information about the player and its relevant methods
class Player {
private:
	// to store the name
	string name;
	// different utilities the player has
	int frustrationLevel, dogecoins, computer, internetProviderLevel, vpn;
	int computerParts[7], antivirus, hackersDeafeated, carmenProgress, virus;
	int computerMaintenanceLevel;
	// computer parts name
	string computerPartsName[7] = { "CPU","GPU","Power Supply Unit","Computer Case","Internet Card","Keyboard and Mouse","Premade Computer" };
public:
	Player();
	void increaseFrustrationLevel(int inc);
	int getFrustrationLevel();
	void increaseAntivirus(int inc);
	void setInternetProviderLevel(int lvl);
	void increaseVpn(int inc);
	int getComputerMaintenanceLevel();
	int getCarmenProgress();
	void getName();
	bool addComputerPart(int idx, int qty);
	bool buy(int price, int idx = -1, int qty = -1);
	void displayStatusUpdate();
	void misfortune();
	void checkMaintenance();
	void repairComputer();
	void getDogecoin();
	void checkVirusInfection();
	bool dropMaintenanceIfVirus();
	bool fightHacker(int room);
	void loseParts();
	void useAntivirus();
	void afterHackerBattle(int room, bool isFinal, bool won);
	void takeNPCChance();
	void puzzleWon();
	void dropFrustrationLevel(int p);
	void endGame(string st);
};

#endif