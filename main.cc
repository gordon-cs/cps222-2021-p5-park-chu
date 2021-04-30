/**/

#include "RoadMap.h"
#include <stdio.h>
#include <iostream>
#include <string>
using std::fstream;
using std::cout;
using std::endl;

int main() {
	while (!eof(std::cin))
	// .... main function goes here....
}

bool eof () {
	char c;
	std::cin >> c;
	if (std::cin.eof()) {
		return true;
	}
	
	else {
		std::cin.unget();
		return false;
	}
}