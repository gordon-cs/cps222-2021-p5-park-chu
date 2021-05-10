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

	//Print
	void print();		//print all roads and towns

	//Public Variables
	Town* thisTown;
	Road* thisRoad;

private:
	vector<Town> _towns;
	vector<Road> _roads;
};

#endif
