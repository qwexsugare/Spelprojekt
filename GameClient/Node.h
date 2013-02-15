#ifndef NODE_H
#define NODE_H
#include "Position.h"
class Node
{
private:
	Node* parentNode;
	int G,H,additionalMovmentCost;
	Position position;
	bool wall;
	bool onOpenList,onClosedList;
public:
	Node();
	~Node();
	void setGCost(int g);
	void setHCost(int h);
	void setFCost(int f);
	void setAdditionalCost(int ac);
	int getGCost();
	int getHCost();
	int getFCost();
	int getAdditionalCost();
	void setParent(Node *p);
	Node* getParent();
	void resetCostsAndParent();
	void setPosition(Position p);
	Position getPosition();
	void actAsWall();
	bool isWall();
	bool isOnOpenlist();
	bool isOnClosedList();
	void putOnClosedList();
	void putOnOpenList();
};
#endif