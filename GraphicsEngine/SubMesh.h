//*****************
//	- 12-12-12 - Anders -
//	- Created
//	- 
//*****************

#pragma once

#include "stdafx.h"

struct SubMesh
{
	ID3D10Buffer* buffer;
	int skeletonId;
	int numInfluences;
	int numVerts;
	int materialId;

	SubMesh()
	{

	}
	~SubMesh()
	{
		buffer->Release();
	}
};