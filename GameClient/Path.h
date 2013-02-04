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

	Path(const Path& _path)
	{
		nrOfPoints = _path.nrOfPoints;
		points = new FLOAT2[nrOfPoints];
		for(int i = 0; i < nrOfPoints; i++)
		{
			points[i] = _path.points[i];
		}
	}

	Path(int _nrOfPoints, FLOAT2* _points)
	{
		nrOfPoints = _nrOfPoints;
		points = new FLOAT2[nrOfPoints];
		for(int i = 0; i < nrOfPoints; i++)
			points[i] = _points[i];
	}

	Path& operator=(const Path& _path)
	{
		if(this == &_path)
		{
			return *this;
		}
		else
		{
			nrOfPoints = _path.nrOfPoints;
			points = new FLOAT2[nrOfPoints];
			for(int i = 0; i < nrOfPoints; i++)
			{
				points[i] = _path.points[i];
			}
			return *this;
		}
	}
	
	~Path()
	{
		if(points)
			delete []points;

		int **lol;
	}
};

#endif