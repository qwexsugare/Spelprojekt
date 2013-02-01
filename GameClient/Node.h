#ifndef NODE_H
#define NODE_H

class Node
{
private:
	int g,h,x,y, id,parentX,parentY;
	bool startNode;
	bool endNode;
	bool wall;
public:
	Node(int x, int y);
	Node();

	int getG();
	int getH();
	void setH(int h);
	void setG(int g);
	int getX();
	int getY();
	void setId(int id);
	int getId();
	void setParent(int x,int y);
	void setToEndNode();
	void setToStartNode();
	bool isEndNode();
	bool isStartNode();
	int getParentX();
	int getParentY();
	void actAsWall();
	bool isWall();
	void resetNode(int x, int y);
};

#endif;