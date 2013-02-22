#ifndef MAP_H
#define MAP_H
#include "Node.h"
#include <iostream>
#include "Position.h"

class Map
{
private:
	int width,height;
	bool initialized;
	Node** nodes;
public:
	Map(int width, int height);
	Map();
	~Map();
	Map(const Map &sourceMap);
	Map& operator=(const Map &sourceMap);
	int getWidth();
	int getHeight();
	void resetParents();
	Node* getNode(Position p);
	bool isValidPosition(Position p);
};
#endif