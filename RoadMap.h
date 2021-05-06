/**/
#include <iostream>
#include <string>
#include <list>
using std::string;
using std::list;

/* Road Map */
class RoadMap {

public:

	//Constructor
	RoadMap (std::istream &cin);

	class Town;
	class Road;

	int getNewRoadIndex();

	void getRoad(Road* road, int i) const;
	void getTown(Town* town, string townName) const;

	void print() const;
	void printShortest(string townName) const;

	

private:
	int roadNumber = -1;

	list<Town> _towns;
	list<Road> _roads;

	class Town {

	public:
		//Constructor
		Town();

		//Accessor
		string getName() const;
		int getRoadNumber() const;
		
		int getRoad(int i) const;

		//Mutator
		void setName(string name);
		void addRoad(int i);

	private:
		string _name;
		list<int> _townMap;
	};

	//ROAD
	class Road {
		/* Constructor */
		//Road()

	public:
		//Accessor
		int getIndex() const;
		string getTown1Name() const;
		string getTown2Name() const;
		float getLength() const;
		bool hasBridge() const;

		//Mutator
		void setIndex(int i);
		void setLength(float l);
		void setTown1(Town* town1);
		void setTown2(Town* town2);
		void setHasBridge(bool hasBridge);

	private:
		int _index;
		float _length;
		Town* _town1;
		Town* _town2;
		bool _hasBridge;
	};
};
