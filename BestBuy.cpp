#include "BestBuy.h"
#include "common.h"

using namespace std;

void BestBuy::printInfo(bool firstTime) {
	// function to print the initial info regarding best buy
	string info = "";
	if (firstTime) info += "You have 200 dogecoins, 1 computer and 1 VPN.You will\n"
		"need to spend the rest of your money on the following\n"
		"items :\n\n";
	info +=
		"1 - COMPUTER PARTS.If your computer breaks, you need 5\n"
		"computer parts to make a new one.\n"
		"2 - ANTIVIRUS SOFTWARE.If your computer is infected with a\n"
		"virus, use the antivirus software to get rid of it.\n"
		"3 - VIRTUAL PRIVATE NETWORK(VPN).The more VPNs you have\n"
		"the harder it is for a hacker to infect your computer with\n"
		"a virus.\n"
		"4 - INTERNET PROVIDER.The better the internet provider, the\n"
		"more reliable your hacking will be.\n\n";
	if (firstTime) info += "You can spend all of your money here before you start your\n"
		"journey, or you can save some to spend on a different\n"
		"electronics site along the way.But beware, some of the\n"
		"websites online are shady, and they won’t always give you a\n"
		"fair price...\n";
	// output the info
	cout << info << endl;
}

void BestBuy::getBuyCategory(int room, bool firstTime) {
	// take category choice from user to buy from best buy
	int choice, cost = 0;
	while (1) {
		// first print  info
		printInfo(firstTime);
		firstTime = false;
		// ask the user to enter category
		cout << "Enter the category number to buy (0 to start the game): ";
		cin >> choice;
		// switch on the basis of choice
		switch (choice) {
		case 0:
			cout << "Total cost so far is: " << cost << endl;
			return;
		case 1:
			// buy computer parts
			cost += buyComputerParts(room);
			break;
		case 2:
			// buy antivirus
			cost += buyAntivirus(room);
			break;
		case 3:
			// buy vpns
			cost += buyVPN(room);
			break;
		case 4:
			// buy IP
			cost += buyIP(room);
			break;
		default:
			// in case of invalid choice
			cout << "Invalid choice. Try again.\n";
		}
	}
}

int BestBuy::buyComputerParts(int room) {
	// initial variables, including the price for each computer part
	int choice, qty, cost = 0, price[] = { 10,20,5,15,5,10,100 };
	// this switch case is if user is in room other than 1
	// then increase the prices as indicated
	switch (room) {
	case 2:
		// increase 10%
		for (int i = 0; i < 7; i++) {
			price[i] += (price[i] * 0.1);
		}
		break;
	case 3:
		// increase 20%
		for (int i = 0; i < 7; i++) {
			price[i] += (price[i] * 0.2);
		}
		break;
	case 4:
		// increase 25%
		for (int i = 0; i < 7; i++) {
			price[i] += (price[i] * 0.25);
		}
		break;
	case 5:
		// increase 30%
		for (int i = 0; i < 7; i++) {
			price[i] += (price[i] * 0.3);
		}
		break;
	}
	while (1) {
		// print info
		string info = "Best Buy recommends that the player should purchase at least 1 of each computer part\n"
			"in case your main computer breaks.You can have a maximum of 3 of each computer\n"
			"part and 1 extra premade computer.These are the different parts\n\n"
			"1 - A CPU costs 10 Dogecoins\n"
			"2 - A GPU costs 20 Dogecoins\n"
			"3 - A Power Supply Unit costs 5 Dogecoins\n"
			"4 - A Computer Case costs 15 Dogecoins\n"
			"5 - An internet card costs 5 Dogecoins\n"
			"6 - A keyboard and mouse costs 10 Dogecoins\n"
			"7 - A premade computer costs 100 Dogecoins\n\n"
			"Enter part number to buy (0 to quit): ";
		cout << info;
		// ask for choice
		cin >> choice;
		if (choice == 0) return cost;
		// ask for quantity
		cout << "Enter quantity: ";
		cin >> qty;
		// check if player can buy this quantity
		if (p.addComputerPart(choice - 1, qty)) {
			// check if player has enough coin to buy
			if (p.buy(price[choice - 1], choice - 1, qty)) {
				cost += price[choice - 1] * qty;
				// print current total cost
				cout << "Total cost so far is: " << cost << endl;
			}
		}
	}
}

int BestBuy::buyAntivirus(int room) {
	// variables, including the cost for a single antivrus usb
	int qty, cost = 0, price = 10;
	// this switch case is if user is in room other than 1
	// then increase the prices as indicated
	switch (room) {
	case 2:
		// 10%
		price += (price * 0.1);
		break;
	case 3:
		// 20%
		price += (price * 0.2);
		break;
	case 4:
		// 25%
		price += (price * 0.25);
		break;
	case 5:
		// 30%
		price += (price * 0.3);
		break;
	}
	while (1) {
		// print info
		string info = "One USB stick of antivirus software costs 10 Dogecoins and will give you a one-time use\n"
			"to get rid of any viruses on your computer.\n\n"
			"Enter quantity to buy (0 to quit): ";
		cout << info;
		// ask for quantity
		cin >> qty;
		// return if zero
		if (qty == 0) return cost;
		// buy the usb for antivirus
		if (p.buy(qty * price)) {
			// increase its count the player has
			p.increaseAntivirus(qty);
			cost += qty * price;
			cout << "Total cost so far is: " << cost << endl;
		}
	}
}

int BestBuy::buyVPN(int room) {
	// quantity, cost and price of single VPN
	int qty, cost = 0, price = 20;
	// this switch case is if user is in room other than 1
	// then increase the prices as indicated
	switch (room) {
	case 2:
		// 10%
		price += (price * 0.1);
		break;
	case 3:
		// 20%
		price += (price * 0.2);
		break;
	case 4:
		// 25%
		price += (price * 0.25);
		break;
	case 5:
		// 30%
		price += (price * 0.3);
		break;
	}
	while (1) {
		// print info
		string info = "A VPN costs 20 Dogecoins each. VPNs reduce your chances of getting hacked by"
			"preventing hackers from tracking down your main computer.The increase in security"
			"maxes out at 2 VPNs.\n\n"
			"Enter quantity to buy (0 to quit): ";
		cout << info;
		// ask for quantity
		cin >> qty;
		// return if 0
		if (qty == 0) return cost;
		// buy the quantity and increase its count afterwards
		if (p.buy(qty * price)) {
			p.increaseVpn(qty);
			cost += qty * price;
			cout << "Total cost so far is: " << cost << endl;
		}
	}
}

int BestBuy::buyIP(int room) {
	int lvl, cost = 0, price[] = { 10,25,40,50 };
	// this switch case is if user is in room other than 1
	// then increase the prices as indicated
	switch (room) {
	case 2:
		// 10%
		for (int i = 0; i < 4; i++) {
			price[i] += (price[i] * 0.1);
		}
		break;
	case 3:
		// 20%
		for (int i = 0; i < 4; i++) {
			price[i] += (price[i] * 0.2);
		}
		break;
	case 4:
		// 25%
		for (int i = 0; i < 4; i++) {
			price[i] += (price[i] * 0.25);
		}
		break;
	case 5:
		// 30%
		for (int i = 0; i < 4; i++) {
			price[i] += (price[i] * 0.3);
		}
		break;
	}
	while (1) {
		// print info
		string info = "Having a better internet provider increases the player’s chances of winning a hacker"
			" battle.\n"
			"Internet provider level 2 costs 10 Dogecoins\n"
			"Internet provider level 3 costs 25 Dogecoins\n"
			"Internet provider level 4 costs 40 Dogecoins\n"
			"Internet provider level 5 costs 50 Dogecoins\n\n"
			"Enter level to buy (0 to quit): ";
		cout << info;
		// input level
		cin >> lvl;
		// return if 0
		if (lvl == 0) return cost;
		// buy that level and set player's level accordinly
		if (p.buy(price[lvl - 2])) {
			p.setInternetProviderLevel(lvl);
			cost += price[lvl - 2];
			cout << "Total cost so far is: " << cost << endl;
		}
	}
}