#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <string>

using namespace std;

class Puzzle {
private:
	string q, ans;
	bool taken;
public:
	Puzzle(string q, string ans);
	void setTaken(bool t);
	bool getTaken();
	bool answerPuzzle();
};

#endif