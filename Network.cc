/*Define the methods of Network*/
#include "Network.h"
#include "Road.h"
#include "Town.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::map;
using std::stack;

//consttructor
Network::Network()
{}

//Mutator
void Network::setNetwork(std::istream& cin) {
	string townName, startTown, endTown;
	char bridge;
	bool b_bridge;
	float roadLength;
	int numRoad, numTown;

	cin >> numTown >> numRoad;

	for (int i = 0; i < numTown; i++) {
		cin >> townName;
		addTown(townName);
	}

	for (int i = 0; i < numRoad; i++) {
		cin >> startTown >> endTown >> bridge >> roadLength;

		if (bridge == 'N') {
			b_bridge = false;
		}
		else {
			b_bridge = true;
		}

		addRoad(i, roadLength, startTown, endTown, b_bridge);
		addRoadToTown(startTown, i);
		addRoadToTown(endTown, i);
	}
}

void Network::addTown(string name) {
	Town newTown;
	newTown.setName(name);
	_towns.push_back(newTown);
}

void Network::addRoadToTown(string name, int i) {
	int index = 0;
	while (_towns[index].getName() != name) {
		index++;
	}
	_towns[index].addRoad(i);
}

//Accessor
void Network::addRoad(int i, float l, string town1, string town2, bool hasBridge) {
	Road newRoad;
	newRoad.setIndex(i);
	newRoad.setLength(l);
	newRoad.setTown1(town1);
	newRoad.setTown2(town2);
	newRoad.setHasBridge(hasBridge);
	_roads.push_back(newRoad);
}

void Network::getTown(string name) {
	int index = 0;
	while (_towns[index].getName() != name) {
		index++;
	}
	thisTown = &_towns[index];
}
void Network::getRoad(int i) {
	thisRoad = &_roads[i];
}

int Network::getTownSize() {
	return _towns.size();
}

int Network::getRoadSize() {
	return _roads.size();
}

bool Network::isInTown(string x) {
	for (int i = 0; i < _towns.size(); i++) {
		if (_towns[i].getName() == x)
			return true;
	}
	return false;
}

//Print
void Network::print() {
	//The town that has travelled to
	vector<string> wentTowns;
	//The towns that are connected by a road to the current town
	queue<string> connectTowns;
	bool hasWent;

	cout << "The input data is:" << endl;
	cout << endl;

	getTown(_towns[0].getName());
	do {
		wentTowns.push_back(thisTown->getName());
		cout << thisTown->getName() << endl;

		for (int road_i = 0; road_i < thisTown->getRoadSize(); road_i++) {

			getRoad(thisTown->getRoad(road_i));
			cout << "        "
				<< (thisRoad->getTown1() == thisTown->getName() ?
					thisRoad->getTown2() : thisRoad->getTown1())
				<< " " << thisRoad->getLength() << " mi"
				<< (thisRoad->getHasBridge() ? " via bridge" : "")
				<< endl;

			connectTowns.push((thisRoad->getTown1() == thisTown->getName() ?
				thisRoad->getTown2() : thisRoad->getTown1()));
		}

		while (!connectTowns.empty()) {
			hasWent = false;
			for (int i = 0; i < (signed)wentTowns.size(); i++) {
				if (connectTowns.front() == wentTowns[i]) {
					hasWent = true;
					break;
				}
			}

			if (!hasWent) {
				getTown(connectTowns.front());
				connectTowns.pop();
				break;
			}
			connectTowns.pop();
		}
		
	} while (!connectTowns.empty());
}

void Network::printShortest() {
	vector<string> orderTowns;
	string temp;
	string name = _towns[0].getName();	//name of the capital
	int currentIndex;

	//sort other towns in alphabetical order
	orderTowns.push_back(name);
	for (int i = 0; i < getTownSize(); i++) {
		getTown(_towns[i].getName());
		if (thisTown->getName() != name) {
			orderTowns.push_back(thisTown->getName());
			currentIndex = orderTowns.size() - 1;
			while (currentIndex > 1 &&
				orderTowns[currentIndex] < orderTowns[currentIndex - 1]) {
				temp = orderTowns[currentIndex];
				orderTowns[currentIndex] = orderTowns[currentIndex - 1];
				orderTowns[currentIndex - 1] = temp;
				currentIndex--;
			}
		}
	}

	//use Dijkstra's algorithm to find the shortest path
	map<string, float> townDistance;	//-1 as INF
	string connectTown;

	townDistance.insert(std::pair<string, int>(name, 0));
	for (int i = 1; i < orderTowns.size(); i++) {
		townDistance.insert(std::pair<string, int>(orderTowns[i], -1));
	}

	for (int i = 0; i < orderTowns.size(); i++) {
		getTown(orderTowns[i]);
		for (int j = 0; j < thisTown->getRoadSize(); j++) {
			getRoad(thisTown->getRoad(j));
			connectTown = (thisRoad->getTown1() == thisTown->getName() ?
				thisRoad->getTown2() : thisRoad->getTown1());
			
			if (townDistance[connectTown] == -1 || townDistance[connectTown] >
				townDistance[thisTown->getName()] + thisRoad->getLength()) {
				townDistance[connectTown] = townDistance[thisTown->getName()] + thisRoad->getLength();
			}
		}
	}

	//print out
	float count;
	stack<string> track;

	cout << "The shortest paths from " << name << " are:" << endl;
	cout << endl;

	for (int i = 1; i < orderTowns.size(); i++) {
		cout << "    The shortest path from " << name << " to " << orderTowns[i] << " is "
			<< townDistance[orderTowns[i]] << " mi:" << endl;

		//print track
		getTown(orderTowns[i]);
		track.push(orderTowns[i]);
		count = townDistance[orderTowns[i]];

		while (count != 0) {
			for (int j = 0; j < thisTown->getRoadSize(); j++) {
				getRoad(thisTown->getRoad(j));
				connectTown = (thisRoad->getTown1() == thisTown->getName() ?
					thisRoad->getTown2() : thisRoad->getTown1());

				if (townDistance[connectTown] == count - thisRoad->getLength()) {
					count -= thisRoad->getLength();
					track.push(connectTown);
					getTown(connectTown);
					break;
				}
			}
		}

		while (!track.empty()) {
			cout << "        " << track.top() << endl;
			track.pop();
		}
	}
}

void Network::printMST() {
	vector <int> orderRoads;
	int currentIndex;
	int temp;
	Road* previousRoad;
	Road* currentRoad;

	//sort road; from shortest road to longest road
	for (int i = 0; i < getRoadSize(); i++) {
		getRoad(_roads[i].getIndex());

		orderRoads.push_back(thisRoad->getIndex());
		currentIndex = orderRoads.size() - 1;
		currentRoad = &_roads[orderRoads[currentIndex]];
		previousRoad = &_roads[orderRoads[currentIndex - 1]];

		while ( currentIndex > 0 && 
			currentRoad->getLength() < previousRoad->getLength()) {
				temp = orderRoads[currentIndex];
				orderRoads[currentIndex] = orderRoads[currentIndex -1];
				orderRoads[currentIndex - 1] = temp;
				currentIndex --;
				currentRoad = &_roads[orderRoads[currentIndex]];
				previousRoad = &_roads[orderRoads[currentIndex - 1]];
			}
	}

	// print MST - Kruskal's Algorithm
	map <string, int> group;
	queue <int> track;
	int count = 0;
	int groupCount = -1;
	int alterCount;
	int alteredCount;
	string town1;
	string town2;

	//initiate groups
	for (int i = 0; i < getTownSize(); i++) {
		group.insert(std::pair<string, int> (_towns[i].getName(), -1));
	}

	getTown(_towns[0].getName());
	for (int i = 0; i < orderRoads.size(); i++) {
		getRoad(orderRoads[i]);
		town1 = thisRoad->getTown1();
		town2 = thisRoad->getTown2();
		
		if ((group[town1] == -1 && group[town2] == -1) || (group[town1] != group[town2])) {
			if ((group[town1] == -1 && group [town2] != -1)
				|| (group[town1] != -1 && group [town2] == -1)) {

				alterCount = (group[town1] == -1 ? group[town2] : group[town1]);

				if (group[town1] == -1) {
					group[town1] = alterCount;
				}

				else {
					group[town2] = alterCount;
				}

				track.push(thisRoad->getIndex());
			}

			else if (group[town1] != -1 && group [town2] != -1) {
				alterCount = group[town1];
				alteredCount = group[town2];

				track.push(thisRoad->getIndex());
				
				for (i = 0; i < _towns.size(); i++) {
					if (group[_towns[i].getName()] == alteredCount) {
						group[_towns[i].getName()] = alterCount;
					}
				}
			}

			else {
				groupCount ++;
				group[town1] = groupCount;
				group[town2] = groupCount;
				track.push(thisRoad->getIndex());
			}
		}
	}
	
	cout << "The road upgrading goal can be achieved at minimal cost by upgrading:" << endl;

	while (! track.empty()) {
		 getRoad(track.front());
		 cout << "    "
		 	  << thisRoad->getTown1()
			  << " to "
			  << thisRoad->getTown2()
			  << endl;

		 track.pop();
	}
}

void Network::printStormIsolation() {
	map<string, int> groups;
	vector<string> arrivedTowns;
	queue<string> connectTowns;
	bool hasArrived;
	int count = 0;
	int groupCount = 0;

	//initiate groups
	for (int i = 0; i < getTownSize(); i++) {
		groups.insert(std::pair<string, int>(_towns[i].getName(), -1));
	}

	//sorting
	getTown(_towns[0].getName());
	while (count <= _towns.size()) {

		//check whether this town has been to before
		hasArrived = false;
		if (arrivedTowns.empty()) {
			arrivedTowns.push_back(thisTown->getName());
		}
		else {
			for (int i = 0; i < arrivedTowns.size(); i++) {
				if (thisTown->getName() == arrivedTowns[i]) {
					hasArrived = true;
					break;
				}
			}
			if (!hasArrived)
				arrivedTowns.push_back(thisTown->getName());
		}

		if (!hasArrived) {
			for (int j = 0; j < thisTown->getRoadSize(); j++) {
				getRoad(thisTown->getRoad(j));
				if (!thisRoad->getHasBridge()) {
					connectTowns.push(thisRoad->getTown1() == thisTown->getName() ?
						thisRoad->getTown2() : thisRoad->getTown1());
				}
			}
		}

		//Adding towns to different group in groups
		bool isAdded;
		bool hasAllArrived = true;

		if (connectTowns.empty()) {
			groups[thisTown->getName()] = groupCount;
			for (int k = 0; k < getTownSize(); k++) {
				if (groups[_towns[k].getName()] == -1) {
					getTown(_towns[k].getName());
					groups[thisTown->getName()] = ++groupCount;
					hasAllArrived = false;
					count++;
					break;
				}
			}
			if (hasAllArrived) {
				break;
			}
		}
		else {
			if (!hasArrived) {
				groups[thisTown->getName()] = groupCount;
				count++;
			}
			getTown(connectTowns.front());
			connectTowns.pop();
		}
	}

	//print out
	vector<string> orderTowns;	//set every group of town in alphabetical order
	int currentIndex;
	string temp;

	cout << "Connected components in event of a major storm are:" << endl;

	for (int i = 0; i <= groupCount; i++) {
		for (int j = 0; j < groups.size(); j++) {
			if (groups[_towns[j].getName()] == i) {
				orderTowns.push_back(_towns[j].getName());
				currentIndex = orderTowns.size() - 1;
				while (currentIndex > 0 &&
					(orderTowns[currentIndex] < orderTowns[currentIndex - 1] || j == 0) &&
					orderTowns[currentIndex - 1] != _towns[0].getName()) {
					temp = orderTowns[currentIndex];
					orderTowns[currentIndex] = orderTowns[currentIndex - 1];
					orderTowns[currentIndex - 1] = temp;
					currentIndex--;
				}
			}
		}
		cout << "   If all bridges fail, the following towns would form an isolated group:" << endl;
		for (int j = 0; j < orderTowns.size(); j++) {
			cout << "        " << orderTowns[j] << endl;
		}
		cout << endl;
		orderTowns.clear();
	}
}