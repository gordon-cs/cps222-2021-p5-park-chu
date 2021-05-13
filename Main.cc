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

		network.print();
		cout << endl;
		cout << "-------------------------------------------------------------------------" <<endl;
		cout << endl;
		network.printShortest();
		cout << endl;
		cout << "-------------------------------------------------------------------------" <<endl;
		cout << endl;
		network.printMST();
		cout << endl;
		cout << "-------------------------------------------------------------------------" <<endl;
		cout << endl;
		network.printStormIsolation();
		cout << endl;
		cout << "End of Report" << endl;

		done = true;
	}

	return 0;
}