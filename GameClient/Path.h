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
		if(_path.nrOfPoints > 0)
		{
			nrOfPoints = _path.nrOfPoints;
			points = new FLOAT2[nrOfPoints];
			for(int i = 0; i < nrOfPoints; i++)
			{
				points[i] = _path.points[i];
			}
		}
		else
		{
			nrOfPoints = 0;
			points = NULL;
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
			if(nrOfPoints > 0)
			{
				delete[] points;
				points = NULL;
				nrOfPoints = 0;
			}
			if(_path.nrOfPoints > 0)
			{
				nrOfPoints = _path.nrOfPoints;
				points = new FLOAT2[nrOfPoints];
				for(int i = 0; i < nrOfPoints; i++)
				{
					points[i] = _path.points[i];
				}
			}

			return *this;
		}
	}
	
	~Path()
	{
		if(points)
			delete []points;
	}
};

#endif