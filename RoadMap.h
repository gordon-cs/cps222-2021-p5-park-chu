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

	//getNewRoadIndex	roadNumber++; return roadNumber;
	int getNewRoadIndex();

	void getRoad(Road* road, int i) const;

	

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
		
		bool hasRoadTo(string town);

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
		bool hasTown(string town);

	private:
		int _index;
		Town* _town1;
		Town* _town2;
		bool _hasBridge;
	};
};
