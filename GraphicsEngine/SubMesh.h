#pragma once

#include "stdafx.h"

struct SubMesh
{
	ID3D10Buffer* buffer;
	ID3D10ShaderResourceView* diffuse;
	int skeletonId;
	int numInfluences;
	int numVerts;
	int materialId;

	SubMesh(ID3D10Buffer* _buffer, int _nrOfVertices)
	{
		this->buffer = _buffer;
		this->numVerts = _nrOfVertices;
		this->diffuse = NULL;
	}
	~SubMesh()
	{
		if(buffer)
			buffer->Release();
		if(this->diffuse)
			diffuse->Release();
	}
}; 