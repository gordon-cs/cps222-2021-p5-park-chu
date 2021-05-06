/**/
#include <iostream>
#include <string>
#include <list>
using std::string;
using std::list;

class RoadMap {

public:

	//Constructor
	RoadMap();

	class Town;
	class Road;

	int getNewRoadIndex();

	void getRoad(Road* road, int i) const;

	void print() const;
	void printShortest(string townName) const;

	

private:
	int roadNumber = -1;

	list<Town> _towns;
	list<Road> _roads;

public:
	class Town {

	public:
		//Constructor
		Town();

		//get
		string getName() const;
		int getRoadNumber() const;
		
		int getRoad(int i) const;

		//......

		//set
		void setName(string name);
		void addRoad(int i);

	private:
		string _name;
		list<int> _townMap;
	};

	//ROAD
	class Road {

	public:
		string getTown1Name() const;
		string getTown2Name() const;
		long getLength() const;
		bool hasBridge() const;

	private:
		int _index;
		long _length;
		Town* _town1;
		Town* _town2;
		bool _hasBridge;
	};
};
