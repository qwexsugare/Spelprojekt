#include "Node.h"

Node::Node()
{
	this->wall=false;
	this->parentNode=0;
	this->G=0;
	this->H=0;
	this->additionalMovmentCost=0;
	this->onOpenList=false;
	this->onClosedList=false;
}
Node::~Node()
{
}
bool Node::isOnClosedList()
{
	return this->onClosedList;
}
bool Node::isOnOpenlist()
{
	return this->onOpenList;
}
void Node::putOnClosedList()
{
	this->onClosedList=true;
	this->onOpenList=false;
}
void Node::putOnOpenList()
{
	this->onOpenList=true;
	this->onClosedList=false;
}
void Node::setAdditionalCost(int ac)
{
	this->additionalMovmentCost=ac;
}

void Node::setGCost(int g)
{
	this->G=g;
}
void Node::setHCost(int h)
{
	this->H=h;
}
int Node::getGCost()
{
	return this->G;
}
int Node::getHCost()
{
	return this->H;
}
int Node::getFCost()
{
	return this->G+this->H;
}
int Node::getAdditionalCost()
{
	return this->additionalMovmentCost;
}
void Node::setParent(Node *p)
{
	this->parentNode=p;
}
Node* Node::getParent()
{
	return this->parentNode;
}
void Node::resetCostsAndParent()
{
	this->parentNode=0;
	this->H=0;
	this->G=0;
	this->onOpenList=false;
	this->onClosedList=false;
}
void Node::setPosition(Position p)
{
	this->position=p;
}
Position Node::getPosition()
{
	return this->position;
}
void Node::actAsWall()
{
	this->wall=true;
}
bool Node::isWall()
{
	return this->wall;
}