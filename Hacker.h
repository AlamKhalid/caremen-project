#ifndef HACKER_H
#define HACKER_H

#include <iostream>
#include <string>

using namespace std;

class Hacker {
private:
	string name;
	int serverRoom;
	bool isDefeated;
public:
	Hacker();
	Hacker(string n, int s);
	string getName();
	void setIsDefeated(bool df);
	bool getIsDefeated();
};

#endif