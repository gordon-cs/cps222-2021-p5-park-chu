/*Define the variables and method names of Network*/
#ifndef NETWORK_H
#define NETWORK_H

#include "Road.h"
#include "Town.h"
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;

class Network {

public:
	//consttructor
	Network();

	//Mutator
	void setNetwork(std::istream& cin);

	void addTown(string name);
	void addRoadToTown(string name, int i);

	void addRoad(int i, float l, string town1, string town2, bool hasBridge);

	//Accessor
	void getTown(string name);	//use name to find the town
	void getRoad(int i);	//use index to find the road

	int getTownSize();	//return size of _towns
	bool isInTown(string x); //check town name x is in _towns

	//Print
	void print();		//print all roads and towns
	void printShortest();	//print shortest distance between two towns
	void printStormIsolation(); //print the isolated group(s) during a strom event

	//Public Variables
	Town* thisTown;
	Road* thisRoad;

private:
	vector<Town> _towns;
	vector<Road> _roads;
};

#endif
