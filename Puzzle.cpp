#include "Puzzle.h"

using namespace std;

// constructor
Puzzle::Puzzle(string q, string ans) {
	this->q = q;
	this->ans = ans;
	taken = false;
}

// setter for taken
void Puzzle::setTaken(bool t) {
	taken = t;
}

// getter for taken
bool Puzzle::getTaken() {
	return taken;
}

// output question and takes ans as input, and checks if ans matches or not
bool Puzzle::answerPuzzle() {
	string a;
	cout << q << endl;
	cin >> a;
	if (a == ans) return true;
	return false;
}