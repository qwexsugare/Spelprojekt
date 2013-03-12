#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "Map.h"
#include "Position.h"
#include "Node.h"
#include "Path.h"
#include <vector>
#include <iostream>

//movments costs for moving in diaglonal or vert/horz
#define DIAGMOVECOST 141
#define NONDIAGMOVECOST 100

using namespace std;

class Pathfinder
{
private:
	vector<Node*> openList,closedList;
	Map map;
	FLOAT2 mapSize;
	int getManhattanDistance(Position p1, Position p2);
	void handleNodesNeighbour(Node* CurrentNode);
	bool handleNeighbour(Node* CurrentNode, Position neighbourPos,int cost);
	sf::Mutex m_mutex;

	//expensive, maybe lookuptables for sqrt
	bool walkableDistance(Position p1, Position p2);
	float distance(Position p1, Position p2);
	int diretion(int x1, int x2);
public:
	Pathfinder(Map map, FLOAT2 mapSize);
	Pathfinder();
	~Pathfinder();
	vector<Position> getPath(Position start, Position end);
	Path getPath(FLOAT2 start, FLOAT2 end);
	bool sameGridPosition(FLOAT2 pos1, FLOAT2 pos2);
	int getWidth();
	bool isValidPos(FLOAT2 _pos);
	int getHeight();
};
#endif