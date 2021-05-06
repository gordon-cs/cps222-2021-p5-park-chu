/**/
#include "RoadMap.h"
#include <iostream>
#include <string>
#include <list>
using std::string;
using std::list;
using std::cout;
using std::endl;

RoadMap::RoadMap (std::istream &cin) {
	Town *town = new Town();
	Road *road = new Road();
	string townName;
	string roadStartTown;
	string roadEndTown;
	char bridge;
	float roadLength;
	int _numRoad;
	int _numTown;

	cin >> _numRoad >> _numTown;

	for (int i = 0; i < _numTown; i++) {
		cin >> townName;
		town -> setName(townName);
		_towns.push_back(*town);
	}

	for (int i = 0; i < _numRoad; i++) {
		cin >> roadStartTown >> roadEndTown >> bridge >> roadLength;

		road -> setIndex(getNewRoadIndex());

		getTown(town, roadStartTown);
		road -> setTown1(town);

		getTown(town, roadEndTown);
		road -> setTown2(town);

		if (bridge == 'B') {
			road -> setHasBridge(true);
		}

		else if (bridge == 'N') {
			road -> setHasBridge(false);
		}

		road -> setLength(roadLength);

		_roads.push_back(*road);
	}
}

int RoadMap::getNewRoadIndex() {
	roadNumber++; 
	return roadNumber;
}

void RoadMap::print() const {
	Road* thisRoad = new Road();

	cout << "The input data is:" << endl;
	cout << endl;

	for (auto it = _towns.cbegin(); it < _towns.size(); ++it) {

		cout << *it->getName() << endl;

		for (int i = 0; i < *it->getRoadNumber(); i++) {

			getRoad(thisRoad, *it->getRoad(i));
			cout << "       "
				<< (*it->getName() == thisRoad->getTown1Name() ?
					thisRoad->getTown2Name() : thisRoad->getTown1Name())
				<< " " << (string)thisRoad->getLength() << " mi"
				<< (thisRoad->hasBridge() ? " via bridge" : "") << endl;
		}
	}
}

void RoadMap::printShortest(string townName) const {
	Road* thisRoad = new Road();

	cout << "The shortest paths from Salem are:" << endl;
	cout << endl;

	for (int i = 0; i < *it->getRoadNumber(); i++) {

		
	}
}

void RoadMap::getRoad(Road* road, int i) const {
	auto road_front = _roads.cbegin();

	while (road_front->getIndex() != i) {
		road_front++;
	}

	road = *road_front;
}

void RoadMap::getTown(Town* town, string townName) const {
	auto town_front = _towns.cbegin();

	while (town_front->getName() != townName) {
		town_front++;
	}

	town = *town_front;
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

//CLASS ROAD
int RoadMap::Road::getIndex() const {
	return _index;
}

string RoadMap::Road::getTown1Name() const {
	return _town1->getName();
}

string RoadMap::Road::getTown2Name() const {
	return _town2->getName();
}

float RoadMap::Road::getLength() const {
	return _length;
}

bool RoadMap::Road::hasBridge() const {
	return _hasBridge;
}

void RoadMap::Road::setIndex(int i) {
	_index = i;
}

void RoadMap::Road::setLength(float l) {
	_length = l;
}

void RoadMap::Road::setTown1(Town* town1) {
	_town1 = town1;
}

void RoadMap::Road::setTown2(Town* town2) {
	_town2 = town2;
}

void RoadMap::Road::setHasBridge(bool hasBridge) {
	_hasBridge = hasBridge;
}
