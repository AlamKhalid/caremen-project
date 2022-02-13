#include <iostream>
#include <string>
#include <unordered_map>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
#include "common.h"
#include "Player.h"
#include "BestBuy.h"
#include "Hacker.h"
#include "Puzzle.h"

using namespace std;
// global variables
Player p;
BestBuy b;
Hacker hackers[5][4];
vector<Puzzle> puzzles;
Game g;

// own sorting algorithm
void sort() {
	// number of items
	const int n = 11;
	int ranking[n] = {2,5,1,9,4,5,1,3,2,7,6}; // dummy data of ranking
	int i, j;
	for (i = 0; i < n - 1; i++)
		// Last i elements are already in place  
		for (j = 0; j < n - i - 1; j++)
			if (ranking[j] > ranking[j + 1]) {
				int temp = ranking[j];
				ranking[j] = ranking[j + 1];
				ranking[j + 1] = temp;
			}
}

// initialize hackers from file
void initHackers() {
	ifstream fin;
	fin.open("hackers.txt");
	string in1, in2;
	int idx, i = 0;
	while (getline(fin, in1, ',')) {
		getline(fin, in2, ',');
		idx = stoi(in2);
		hackers[idx - 1][i++] = Hacker(in1,idx);
		if (i == 4)
			i = 0;
	}
	fin.close();
}

// initialize puzzle from file
void initPuzzle() {
	ifstream fin1, fin2;
	string s1 = "", s2 = "", data;
	fin1.open("puzzles.txt");
	fin2.open("answers.txt");
	while (getline(fin1, data)) {
		s1 += data + "\n";
		while (getline(fin1, data)) {
			if (data != "---") {
				s1 += data + "\n";
			}
			else {
				break;
			}
		}
		while (getline(fin2, data)) {
			if (data != "---") {
				s2 += data + "\n";
			}
			else break;
		}
		puzzles.push_back(Puzzle(s1,s2));
		s1 = "";
		s2 = "";
	}
	fin1.close();
	fin2.close();
}

int main() {
	// random seed
	srand(time(NULL));
	// get user name
	p.getName();
	// initial buy best
	b.getBuyCategory(true);
	// initialize hackers from hackers.txt
	initHackers();
	// initialize puzzle
	initPuzzle();
	// start the game
	g.initMap();
	// play the game
	g.playGame();
	return 0;
}