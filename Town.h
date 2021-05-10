/*Define the variables and method names of Town*/
#ifndef TOWN_H
#define TOWN_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class Town {

public:
	//constructor
	Town();

	//Mutator
	void setName(string x);
	void addRoad(int i);

	//Accessor
	string getName() const;
	int getRoad(int i) const;
	int getRoadSize() const;

private:
	string name;	//name of the town
	vector<int> roads;	//connected roads
};

#endif