#pragma once

#include "stdafx.h"
#include "SubMesh.h"
#include "Material.h"

#include <DirectXCollision.h>

using namespace DirectX;

struct Mesh
{
	int nrOfVertices;
	int numSkeletons;
	vector<SubMesh*> subMeshes;

	vector<Material> materials;
	ID3D10Buffer* buffer;

	BoundingOrientedBox* m_obb;
	BoundingSphere* m_bs;

	bool isAnimated;

	Mesh()
	{
		this->buffer = NULL;
		this->nrOfVertices = 0;
		this->m_obb = NULL;
		this->m_bs = NULL;
		this->numSkeletons = 0;
		this->isAnimated = false;
	}

	Mesh(ID3D10Buffer* _buffer, int _nrOfVertices)
	{
		this->buffer = _buffer;
		this->nrOfVertices = _nrOfVertices;
		this->m_obb = NULL;
		this->m_bs = NULL;
		this->numSkeletons = 0;
		this->isAnimated = false;
	}
	~Mesh()
	{
		if(this->buffer)
			buffer->Release();
		for(int i = 0; i < subMeshes.size(); i++)
		{
			if(subMeshes[i])
				delete subMeshes[i];
		}
		if(this->m_obb)
			delete this->m_obb;
		if(this->m_bs)
			delete this->m_bs;
	}
};