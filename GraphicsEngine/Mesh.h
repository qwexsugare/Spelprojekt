//*****************
//	- 12-12-12 - Anders -
//	- Added vector: subMeshes
//	- Include SubMesh.h
//	- 
//*****************


#pragma once

#include "stdafx.h"
#include "SubMesh.h"

struct Mesh
{
	ID3D10Buffer* buffer;
	int nrOfVertices;
	ID3D10ShaderResourceView* m_texture;

	vector<SubMesh> subMeshes;

	Mesh(ID3D10Buffer* _buffer, int _nrOfVertices)
	{
		buffer = _buffer;
		nrOfVertices = _nrOfVertices;
	}

	~Mesh()
	{
		buffer->Release();
	}
};