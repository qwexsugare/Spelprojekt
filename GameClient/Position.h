#pragma once
class Position
{
private:
	int xp,yp;
public:
	Position(void);
	Position(int x, int y);
	~Position(void);
	void setXY(int x,int y);
	int getX();
	int getY();
};

