//*****************
//	- 12-12-12 - Anders -
//	- Added vector: subMeshes
//	- Include SubMesh.h
//	- 16-12-12 - Anders och Alve -
//	- Include Material.h
//	- Added vector materials
//*****************


#pragma once

#include "stdafx.h"
#include "SubMesh.h"
#include "Material.h"

struct Mesh
{
	ID3D10Buffer* buffer;
	int nrOfVertices;
	ID3D10ShaderResourceView* m_texture;
	int skeletonId;
	vector<SubMesh> subMeshes;
	vector<Material> materials;


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