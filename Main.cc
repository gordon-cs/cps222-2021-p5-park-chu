/*the header of projet5*/
#include "Network.h"
#include <stdio.h>
#include <iostream>
#include <string>
using std::fstream;
using std::cout;
using std::endl;

static const char ESC = 27;

int main() {
	// Main loop
	bool done = false;
	bool isInput = false;
	Network network;

	while (!done) {
		// Check for eof, without changing input
		char c;
		std::cin >> c;
		
		if (std::cin.eof()) {
			done = true;
		}
		else {
			std::cin.unget();
		}

		// .... main function goes here....
		if (!isInput) {
			network.setNetwork(std::cin);
			isInput = true;
		}

		
		cout << ESC << "[f" << ESC << "[2J"	 //set cursor to (0, 0) and clear
			<< "p - print; s - print shortest path from capital; i - isolation" << endl;	//this
			
		std::cin >> c;

		switch (c) {
		case 'p': network.print();		break;
		case 's': network.printShortest();		break;
		case 'i': network.printStormIsolation();	break;
			//more cases
		}

		
		if (c != 'p' && c != 's' && c != 'i') {
			cout << ESC << "[f" << ESC << "[2J"	 //set cursor to (0, 0) and clear
				<< "p - print; s - print shortest path from capital; i - isolation" << endl;	//this		
		}
	}

	return 0;
}