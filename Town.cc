/*Define the methods of Town*/
#include "Town.h"
#include <string>
using std::string;

//constructor
Town::Town()
{}

//Mutator
void Town::setName(string x) {
	name = x;
}

void Town::addRoad(int i) {
	roads.push_back(i);
}

//Accessor
string Town::getName() const {
	return name;
}

int Town::getRoad(int i) const {
	return roads.at(i);
}

int Town::getRoadSize() const {
	return roads.size();
}