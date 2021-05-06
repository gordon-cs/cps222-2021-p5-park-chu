/**/
#include "RoadMap.h"
#include <iostream>
#include <string>
#include <list>
using std::string;
using std::list;
using std::cout;
using std::endl;

int RoadMap::getNewRoadIndex() {
	roadNumber++; 
	return roadNumber;
}

void RoadMap::print() const {
	Road* thisRoad = new Road();

	cout << "The input data is:" << endl;
	cout << endl;

	for (auto it = _towns.cbegin(); it < _towns.size(); it) {

		it++;
		cout << *it->getName() << endl;

		for (int i = 0; i < *it->getRoadNumber(); i++) {

			getRoad(thisRoad, *it->getRoad(i));
			cout << "       "
				<< (*it->getName() == thisRoad->getTown1Name() ?
					thisRoad->getTown2Name() : thisRoad->getTown1Name())
				<< " " << thisRoad->getLength() << " mi"
				<< (thisRoad->hasBridge() ? " via bridge" : "") << endl;
		}
	}
}

void RoadMap::printShortest(string townName) const {
	Road* thisRoad = new Road();

	cout << "The shortest paths from Salem are:" << endl;
	cout << endl;

	for (auto it = _towns.cbegin(); )
}

void RoadMap::getRoad(Road* road, int i) const {
	road = _roads[i];
}

//CLASS TOWN
string RoadMap::Town::getName() const {
	return _name;
}

int RoadMap::Town::getRoadNumber() const {
	return _townMap.size();
}

int RoadMap::Town::getRoad(int i) const {
	auto townmap_front = _townMap.cbegin();
	std::advance(townmap_front, ++i);
	return *townmap_front;
}

void RoadMap::Town::setName(string name) {
	_name = name;
}

void RoadMap::Town::addRoad(int i) {
	_townMap.push_back(i);
}


//......

//CLASS ROAD
string RoadMap::Road::getTown1Name() const {
	return _town1->getName();
}

string RoadMap::Road::getTown2Name() const {
	return _town2->getName();
}

bool RoadMap::Road::hasBridge() const {
	return _hasBridge;
}
