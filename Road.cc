/*Define the methods of Town*/
#include "Road.h"
#include <string>
using std::string;

//consttructor
Road::Road()
{}

//Mutator
void Road::setIndex(int i) {
	index = i;
}

void Road::setLength(float i) {
	length = i;
}

void Road::setTown1(string x) {
	town1 = x;
}

void Road::setTown2(string x) {
	town2 = x;
}

void Road::setHasBridge(bool b) {
	hasBridge = b;
}

//Accessor
int Road::getIndex() const {
	return index;
}

float Road::getLength() const {
	return length;
}

string Road::getTown1() const {
	return town1;
}

string Road::getTown2() const {
	return town2;
}

bool Road::getHasBridge() const {
	return hasBridge;
}