/*Define the methods of Network*/
#include "Network.h"
#include "Road.h"
#include "Town.h"
#include <iostream>
#include <queue>
#include <map>
#include <stack>
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
			cout << "        " << track.top() << endl;;
			track.pop();
		}
	}
}