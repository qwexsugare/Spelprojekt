#ifndef PATH_H
#define PATH_H

#include "DataStructures.h"

struct Path
{
	int nrOfPoints;
	FLOAT2* points;

	Path()
	{
		nrOfPoints = 0;
		points = NULL;
	}

	Path(int _nrOfPoints, FLOAT2* _points)
	{
		nrOfPoints = _nrOfPoints;
		points = _points;
	}

	~Path()
	{
		if(points)
			delete points;
	}
};

#endif