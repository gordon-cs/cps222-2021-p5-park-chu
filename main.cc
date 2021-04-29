/**/

#include "RoadMap.h"
#include <stdio.h>
#include <fstream>
#include <string>
using std::fstream;
using std::cin;
using std::cout;
using std::endl;

int main() {

	string fileName;
	string line;

	cout << "Type file name: " << endl;
	cin >> fileName;


	fstream newfile;
	// open a file to perform write operation
	newfile.open(fileName, ios::out);

	while (getline(newfile, line)) {
		
	}

}