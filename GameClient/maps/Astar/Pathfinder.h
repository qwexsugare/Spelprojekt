#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "Node.h"
#include "Path.h"
#include <vector>
#include <string>

using namespace std;

class Pathfinder
{
private:
	Node **nodes;
	int rows,cols;
	vector<Node> openList;
	vector<Node> closedList;
	int startX,startY,endX,endY;
	int getDistance(int x1,int y1, int x2, int y2);
	bool isOnClosedList(Node node);
	bool isOnOpenList(Node node);
	void checkNeighbor(Node currentNode,int x, int y,bool diag,string dir);
	bool p;

public:
	Pathfinder(int width,int height);
	Pathfinder();
	Path getPath();
	virtual ~Pathfinder();
	bool setStart(int x, int y);
	bool setEnd(int x,int y);
	void reset();
	void setAsWall(int x, int y);

};

#endif