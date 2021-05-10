/*Define the variables and method names of Road*/
#ifndef ROAD_H
#define ROAD_H

#include <string>
using std::string;

class Road {

public:
	//consttructor
	Road();

	//Mutator
	void setIndex(int i);
	void setLength(float i);
	void setTown1(string x);
	void setTown2(string x);
	void setHasBridge(bool b);

	//Accessor
	int getIndex() const;
	float getLength() const;
	string getTown1() const;
	string getTown2() const;
	bool getHasBridge() const;

private:
	int index;	//index of the road
	float length;	//length of the road
	string town1, town2;	//name of the 2 towns the road connects
	bool hasBridge;	//does the road has bridge
};

#endif