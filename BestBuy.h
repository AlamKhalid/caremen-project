#ifndef BESTBUY_H
#define BESTBUY_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// best buy store
class BestBuy {
public:
	void printInfo(bool firstTime);
	void getBuyCategory(int room = 1, bool firstTime = false);
	int buyComputerParts(int room);
	int buyAntivirus(int room);
	int buyVPN(int room);
	int buyIP(int room);
};

#endif