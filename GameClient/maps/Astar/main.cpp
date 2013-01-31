#include <iostream>
#include "Pathfinder.h"
using namespace std;


int main(int argc, char **argv)
{
	Pathfinder pf(10,10);
	
	pf.setStart(0,0);
	pf.setAsWall(1,0);

	pf.setAsWall(4,0);
	pf.setAsWall(4,1);
	pf.setAsWall(4,2);
	pf.setAsWall(5,4);
	pf.setAsWall(5,5);
	pf.setAsWall(6,1);
	pf.setAsWall(6,2);
	pf.setAsWall(6,3);
	pf.setAsWall(8,0);
	pf.setEnd(-1,0); 
	
	cout <<pf.getPath()<<endl;
	
	int t;
	cin >>t;
	return 0;
}
