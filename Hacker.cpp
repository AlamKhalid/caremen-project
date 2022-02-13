#include "Hacker.h"

using namespace std;

// default constructor
Hacker::Hacker() {}

// parameterized constructor
Hacker::Hacker(string n, int s) {
	name = n;
	serverRoom = s;
	isDefeated = false;
}

// getter for name
string Hacker::getName() {
	return name;
}

// setter for isDefeated
void Hacker::setIsDefeated(bool df) {
	isDefeated = df;
}

// getter for isDeafeated
bool Hacker::getIsDefeated() {
	return isDefeated;
}