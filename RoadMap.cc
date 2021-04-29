/**/
#include "RoadMap.h"
#include <iostream>
#include <string>
#include <list>
using std::string;
using std::list;

int RoadMap::getNewRoadIndex() {

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

bool RoadMap::Town::hasRoadTo(string town) {
	int size = _townMap.size();
	Road* currentRoad = new Road();
	for (int i = 0; i < size; i++) {
		getRoad(currentRoad, i);
		if (currentRoad.hasTown(town))
			return true;
	}
	return false;
}

void RoadMap::Town::setName(string name) {
	_name = name;
}

void RoadMap::Town::addRoad(int i) {
	_townMap.push_back(i);
}


//......

//CLASS ROAD
bool RoadMap::Road::hasTown(string town) {
	if (_town1 == town || _town2 == town)
		return true;
	else
		return false;
}
