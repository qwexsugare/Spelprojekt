#include "Position.h"


Position::Position(void)
{
	this->xp=0;
	this->yp=0;
}
Position::Position(int x, int y)
{
	this->xp=x;
	this->yp=y;
}

Position::~Position(void)
{
}
void Position::setXY(int x, int y)
{
	this->xp=x;
	this->yp=y;
}
int Position::getX()
{
	return this->xp;
}
int Position::getY()
{
	return this->yp;
}