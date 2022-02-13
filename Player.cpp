#include "Player.h"

using namespace std;

// constructor, to initalize the utilities the player has
Player::Player() {
	frustrationLevel = 0;
	dogecoins = 200;
	computer = 1;
	internetProviderLevel = 1;
	vpn = 1;
	antivirus = 0;
	virus = 0;
	hackersDeafeated = 0;
	carmenProgress = 0;
	computerMaintenanceLevel = 100;
	for (int i = 0; i < 7;i++)
		computerParts[i] = 0;
}

// increase the frustration level of player by inc amount
void Player::increaseFrustrationLevel(int inc) {
	frustrationLevel += inc;
}

// getter for frustration level of player
int Player::getFrustrationLevel() {
	return frustrationLevel;
}

// increase antivirus the player has by inc amount
void Player::increaseAntivirus(int inc) {
	antivirus += inc;
}

// setter for internet provider level variable
void Player::setInternetProviderLevel(int lvl) {
	internetProviderLevel = lvl;
}

// it increases the vpn for the player by inc amount
void Player::increaseVpn(int inc) {
	vpn += inc;
}

// getter for computer maintenance level
int Player::getComputerMaintenanceLevel() {
	return computerMaintenanceLevel;
}

// getter for carmen progress
int Player::getCarmenProgress() {
	return carmenProgress;
}

// function which takes the name for the player, called at the start of main
void Player::getName() {
	cout << "Enter player's name: ";
	cin >> name;
}

// function to check whether the user can buy a certain part, reffering to quantity
bool Player::addComputerPart(int idx, int qty) {
	// check for premade computer
	if (idx == 6 && computerParts[idx] + qty > 1) {
		cout << "You can only have 1 premade computer\n";
		return false;
	}
	// condition for other parts, not more than 3
	else if (computerParts[idx] + qty > 3) {
		cout << "You can only have 3 of each computer part\n";
		return false;
	}
	else {
		// in case the item can be bought
		return true;
	}
}

// check whether the user has the money to buy the utility
bool Player::buy(int price, int idx, int qty) {
	// success condition
	if (dogecoins - price >= 0) {
		if (idx != -1) computerParts[idx] += qty;
		cout << "Item bought successfully\n";
		dogecoins -= price;
		return true;
	}
	// in case not enough coins
	else {
		cout << "Not enough dogecoins. Choose another quantity next time.\n";
		return false;
	}
}

// display status update
void Player::displayStatusUpdate() {
	cout << "Computer's current maintenance level: " << computerMaintenanceLevel << endl;
	cout << "Viruses computer has: " << virus << endl;
	cout << "Computer parts available\n";
	for (int i = 0; i < 6; i++) {
		cout << computerPartsName[i] << ": " << computerParts[i] << endl;
	}
	cout << "Antivirus USB sticks: " << antivirus << endl;
	cout << "VPNs available: " << vpn << endl;
	cout << "Internet provider level: " << internetProviderLevel << endl;
	cout << "Dogecoins available: " << dogecoins << endl;
	cout << "Player's frustration level: " << frustrationLevel << endl;
	cout << "Carmen's progress: " << carmenProgress << endl;
	cout << "Hackers the player has defeated so far: " << hackersDeafeated << endl;
}

// occur misfortune
void Player::misfortune() {
	// randomly choose a misfortune event
	int event = rand() % 3 + 1;
	// indicate a lost of computer part
	bool lost = false;
	switch (event) {
	case 1:
		// loop through all parts and see which can be lost
		for (int i = 0; i < 6; i++) {
			// break once found
			if (computerParts[i] > 0) {
				computerParts[i]--;
				lost = true;
				cout << "OH NO! Your team was robbed by Carmen’s dastardly hackers!\n";
				cout << "You have lost a computer part!" << endl;
				break;
			}
		}
		if (!lost) {
			if (antivirus > 0) {
				antivirus--;
				cout << "OH NO! Your team was robbed by Carmen’s dastardly hackers!\n";
				cout << "You have lost an antivirus USB!" << endl;
				lost = true;
			}
		}
		if (lost) return;
	case 2:
		// drop computer maintenance level
		cout << "OH NO! Your computer was damaged!\n";
		computerMaintenanceLevel -= 10;
		break;
	case 3:
		// third case, increase frustration level
		cout << "OH NO! Why won't my code work!!!!\n"
			"Your frustration level was increased.\n";
		frustrationLevel += 10;
		break;
	}


}

// check computer maintenance
// turns it back to zero if less than zero
void Player::checkMaintenance() {
	if (computerMaintenanceLevel < 0)
		computerMaintenanceLevel = 0;
}

// repair computer
void Player::repairComputer() {
	int part, qty;
	// computer can be repaired only if there are no viruses
	if (virus == 0) {
		// only repair if computer maintenance level is below 100
		if (computerMaintenanceLevel < 100) {
			while (1) {
				// first print inventory
				cout << "INVENTORY:\n";
				for (int i = 0; i < 6; i++) {
					cout << i + 1 << ". " << computerPartsName[i] << ": " << computerParts[i] << endl;
				}
				// ask user to enter part number he would like to use
				cout << "Enter the number of part you would like to use (0 to quit) : ";
				cin >> part;
				// quit condition
				if (part == 0) break;
				// ask for quantity
				cout << "Enter quantity: ";
				cin >> qty;
				// only repair if that quantity is available at users end
				if (computerParts[part - 1] >= qty) {
					computerParts[part - 1] -= qty;
					computerMaintenanceLevel += (qty * 20);
					if (computerMaintenanceLevel > 100) computerMaintenanceLevel = 100;
				}
				// in case entered quantity is not available in inventory
				else {
					cout << "Not enough quantity\n";
				}
			}
		}
		// in case computer maintenance level is already 100
		else {
			cout << "Computer maintenance level is already 100.\n";
		}
	}
	// in case computer has viruses, it cannot be repaired
	else {
		cout << "Your computer has viruses. You cannot repair your computer\n";
	}
}

// increase dogecoin of player after each move
void Player::getDogecoin() {
	dogecoins += 5;
	dogecoins += computerParts[1] * 5;
}

// check virus infection probablity
void Player::checkVirusInfection() {
	int r = rand() % 10 + 1;
	if (r == 1) {
		// infect with virus
		virus++;
	}
}

// at each step, maintenance is dropped, but it is increased if computer has viruses
bool Player::dropMaintenanceIfVirus() {
	if (virus > 0) {
		computerMaintenanceLevel -= (virus * 10);
		if (computerMaintenanceLevel < 0) {
			cout << "Player has lost the game due to virus infection.\n";
			computerMaintenanceLevel = 0;
			return true;
		}
		return false;
	}
	return false;
}

// fighting with hacker
bool Player::fightHacker(int room) {
	// two randomly generated numbers
	int r1 = rand() % 6 + 1;
	int r2 = rand() % 6 + 1;
	// result
	float result = (r1 * internetProviderLevel) - (r2 * room * (1 / float(vpn)));
	// winning condition
	if (result > 0) {
		dogecoins += 50;
		hackersDeafeated++;
		return true;
	}
	// losing condition
	carmenProgress += 25;
	computerMaintenanceLevel -= 20;
	checkVirusInfection();
	return false;
}

// player loses parts
void Player::loseParts() {
	for (int i = 0; i < 6; i++) {
		computerParts[i] = 0;
	}
}

// use antiviris software
void Player::useAntivirus() {
	if (antivirus > 0) antivirus--;
	virus = 0;
}

// after battling the hacker
void Player::afterHackerBattle(int room, bool isFinal, bool won) {
	int r = rand() % 10 + 1;
	// check if room is 5 and that is final hacker, so just return
	if (room == 5 && isFinal && won) return;
	if (r <= 3) {
		// drop maintenance
		computerMaintenanceLevel -= 10;
	}
	for (int i = 0; i < 6; i++) {
		// break once found
		if (computerParts[i] > 0) {
			computerParts[i]--;
			cout << "OH NO! Your team was robbed by Carmen’s dastardly hackers!\n";
			cout << "You have lost a computer part!" << endl;
			break;
		}
	}
}

// take npc chance
void Player::takeNPCChance() {
	int r = rand() % 9 + 1;
	// friendly case
	if (r <= 3) {
		cout << "NPC is your friend.\n";
		int c = rand() % 6;
		cout << "They have given you " << computerPartsName[c] << " for free\n";
		computerParts[c]++;
	}
	// neutral case
	else if (r <= 6) {
		cout << "NPC is netural. Nothing special happens here\n";
	}
	// enemy case
	else {
		cout << "OH NO! NPC is enemy.\n";
		for (int i = 0; i < 6; i++) {
			// break once found
			if (computerParts[i] > 0) {
				computerParts[i]--;
				cout << "You have lost a " << computerParts[i] << endl;
				break;
			}
		}
	}
}

// won puzzle
void Player::puzzleWon() {
	int r = rand() % 6;
	computerParts[r]++;
	cout << "You have won a " << computerPartsName[r] << endl;
}

// drop frustration
void Player::dropFrustrationLevel(int p) {
	frustrationLevel -= p;
	if (frustrationLevel < 0)
		frustrationLevel = 0;
}

// ends the game and display ending stats
void Player::endGame(string st) {
	cout << "Player name: " << name << endl;
	cout << "Hackers Defeated: " << hackersDeafeated << endl;
	cout << "Dogecoins: " << dogecoins << endl;
	// write to file
	ofstream fout;
	fout.open("results.txt", ios_base::app);
	fout << st << "," << name << "," << hackersDeafeated << "," << dogecoins << endl;
	fout.close();
}