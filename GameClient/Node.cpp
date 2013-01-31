#include "Node.h"

Node::Node(int x,int y)
{
	this->parentX=0;
	this->parentY=0;
	this->x=x;
	this->y=y;
	this->g=0;
	this->h=0;
	this->id=0;
	this->endNode=false;
	this->startNode=false;
	this->wall=false;
}
Node::Node()
{
	this->parentX=0;
	this->parentY=0;
	this->id=0;
	this->x=0;
	this->y=0;
	this->g=0;
	this->h=0;
	this->endNode=false;
	this->startNode=false;
	this->wall=false;
}
bool Node::isWall()
{
	return this->wall;
}
void Node::actAsWall()
{
	this->wall=true;
}
int Node::getParentX()
{
	return this->parentX;
}
int Node::getParentY()
{
	return this->parentY;
}

int Node::getX()
{
	return this->x;
}
int Node::getY()
{
	return this->y;
}
int Node::getG()
{
	return this->g;
}
int Node::getH()
{
	return this->h;
}
void Node::setParent(int x, int y)
{
	this->parentX=x;
	this->parentY=y;
}
void Node::setG(int g)
{
	this->g=g;
}
void Node::setH(int h)
{
	this->h=h;
}
void Node::setToEndNode()
{
	this->endNode=true;
}
void Node::setToStartNode()
{
	this->startNode=true;
}
bool Node::isEndNode()
{
	return this->endNode;
}

void Node::setId(int id)
{
	this->id=id;
}

int Node::getId()
{
	return this->id;
}
bool Node::isStartNode()
{
	return this->startNode;
}