#include "Game.h"
#include "common.h"

using namespace std;

void Game::initMap() {
	// use variables to store the values for randomly generated row
	// and column, we use them to place the item on the map
	int row, col;
	// indicate success, it shows whether to continue the loop or not
	bool success;
	// spawn best buy
	do {
		row = rand() % 5;
		col = rand() % 9;
		if (row == 0 && col == 0) continue;
		success = map.spawnBestBuy(row, col);
	} while (!success);
	// randomly generate how many NPC the map will have
	numNPC = rand() % 3 + 1;
	// map.setNPCCount(numNPC);
	// spawn npc the number of times
	for (int i = 0; i < numNPC; i++) {
		do {
			row = rand() % 5;
			col = rand() % 9;
			if (row == 0 && col == 0) continue;
			success = map.spawnNPC(row, col);
		} while (!success);
	}
	// randomly generate how many hackers the map will have
	numHackers = rand() % 3 + 1;
	// map.setHackerCount(numHackers);
	// spawn hackers the number of times
	for (int i = 0; i < numHackers; i++) {
		do {
			row = rand() % 5;
			col = rand() % 9;
			if (row == 0 && col == 0) continue;
			cout << row << "," << col << endl;
			success = map.spawnHacker(row, col);
		} while (!success);
	}

}
void Game::displayOtherMoves(bool dh) {
	// other neccesary moves apart from moving up down left right
	cout << "r (repair your computer)\n";
	cout << "v (use antivirus software)\n";
	cout << "b (browse stackoverflow)\n";
	// only display this is the user has defeated any hacker in the room
	if (dh) cout << "n (next server room)\n";
	cout << "q (quit)\n";
}
void Game::checkMisfortune() {
	int num = rand() % 10 + 1;
	if (num <= 3) {
		// occur misfortune
		p.misfortune();
	}
}
void Game::browseStackoverflow() {
	// implement rock papers scissors
	string c[] = { "Rock", "Papers", "Scissors" };
	int comp = rand() % 3 + 1; // computer chooses randomly
	int choice;
	// prompt for input from user
	cout << "1. Rock\n2. Papers\n3. Scissors\n\nChoice: ";
	cin >> choice; // take input
	// display what player and computer has chosen
	cout << "Computer has chosen " << c[comp - 1] << endl;
	cout << "You have chosen " << c[choice - 1] << endl;
	// display results accordinly
	if (comp == 1 && choice == 2 || comp == 2 && choice == 3 || comp == 3 && choice == 1) {
		cout << "You have won!\nYour frustration level has dropped\n";
		p.dropFrustrationLevel(5);
	}
	else if (choice == comp) {
		cout << "The game is draw\n";
	}
	else {
		cout << "You have lost.\n";
	}
}
void Game::nextRoom() {
	// increase the server room
	serverRoom++;
	// reset map
	map.resetMap();
	// also reinitialize it
	initMap();
}
void Game::playGame() {
	int hackerIdx, choice, hackersEncountered = 0;
	char move;
	bool deafeatedAnyHacker = false, won;
	while (1) {
		p.displayStatusUpdate(); 	// display status update
		map.displayMap();  // pretty print map_data in terminal
		cout << "Valid moves are: " << endl;
		map.displayMoves();  // give user a menu of valid moves to pick from
		displayOtherMoves(deafeatedAnyHacker);
		cout << "Input a move: ";
		cin >> move;
		cout << endl;
		if (move == 'q') {
			cout << "You have quit the game." << endl;
			won = false;
			break;
		}
		map.executeMove(move);  // move the player on map based on user input
		// increase frustration
		p.increaseFrustrationLevel(2);
		// get dogeCoin
		p.getDogecoin();
		// check virus infection
		if (p.dropMaintenanceIfVirus()) break;
		// encoutered buybest
		if (map.isBestBuyLocation()) {
			cout << "You're in a Best Buy!" << endl;
			cout << "Enter 1 to shop 0 to exit\n\nChoice: ";
			cin >> choice;
			if (choice == 1) {
				b.getBuyCategory(serverRoom);
			}
		}
		// encouter hacker
		else if (map.isHackerLocation()) {
			// randomly choose hacker
			hackerIdx = -1;
			for (int i = 0; i < 4; i++) {
				if (!hackers[serverRoom - 1][i].getIsDefeated()) {
					hackerIdx = i;
					break;
				}
			}
			if (hackerIdx != -1) {
				// output hacker name
				cout << "You just ran into " << hackers[serverRoom - 1][hackerIdx].getName() << "! Think you can beat this\n"
					"hacker's skills ?\n";
				// ask user from input
				cout << "1. Attack\n2. Forefeit\n\nChoice: ";
				cin >> choice;
				// attack
				if (choice == 1) {
					// only fight if computer maintenance is above 0
					if (p.getComputerMaintenanceLevel() > 0) {
						won = p.fightHacker(serverRoom);
						// in case the player wins
						if (won) {
							hackers[serverRoom - 1][hackerIdx].setIsDefeated(true);
							hackersEncountered++;
							if (serverRoom == 5) {
								cout << "You have won the game!\n\n";
								break;
							}
						}
					}
					else cout << "Cannot fight hacker since computer maintenance level is 0\n";
				}
			}
			// forefeit
			else {
				cout << "The player was unable to outsmart Carmen’s hacker.\n";
				// player lose parts
				p.loseParts();
			}
			// after maths of hacker battle
			p.afterHackerBattle(serverRoom, hackersEncountered == numHackers, won);

		}
		// in case NPC is encountered
		else if (map.isNPCLocation()) {
			cout << "You've encountered an NPC!" << endl;
			cout << "1. Play Puzzle\n2. Take your chance\n\nChoice: ";
			cin >> choice;
			// play puzzle
			if (choice == 1) {
				int r;
				// randomly choose puzzle
				r = rand() % puzzles.size();
				// play puzzle and if user win, removes it from vector
				if (puzzles[r].answerPuzzle()) {
					p.puzzleWon();
					puzzles.erase(puzzles.begin() + r);
				}
			}
			// take chance as per directed
			else {
				p.takeNPCChance();
			}

		}
		else {
			// switch is for other moves such as repair, stackoverflow etc.
			switch (move) {
			case 'r':
				p.repairComputer();
				break;
			case 'b':
				browseStackoverflow();
				break;
			case 'v':
				p.useAntivirus();
				break;
			case 'n':
				if (deafeatedAnyHacker) {
					// run only if any hacker has been defeated
					nextRoom();
				}
				break;
			default:
				checkMisfortune();
				break;
			}
		}
		// three losing conditions
		// frustration level goes above 100
		if (p.getFrustrationLevel() >= 100) {
			cout << "OH NO! You have rage quit!\n"
				"Looks like you couldn’t handle Carmen’s hackers.\n";
			won = false;
			break;
		}
		// carmen progress goes above 100
		else if (p.getCarmenProgress() >= 100) {
			cout << "You have lost.\nThe hackers succeed in stealing all of the information out of the servers";
			won = false;
			break;
		}
		// computer maintenance gets 0
		else if (p.getComputerMaintenanceLevel() <= 0) {
			cout << "OH NO! You have lost.\nYour computer maintenance level has reached 0.\n";
			won = false;
			break;
		}
	}
	// final output display
	if (won) {
		p.endGame("won");
	}
	else p.endGame("lost");
}