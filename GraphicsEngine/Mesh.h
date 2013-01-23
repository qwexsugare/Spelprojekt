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
	ID3D10ShaderResourceView* m_texture;
	vector<SubMesh*> subMeshes;

	vector<Material> materials;
	ID3D10Buffer* buffer;

	BoundingOrientedBox* m_obb;
	BoundingSphere* m_bs;

	bool isAnimatied;

	Mesh()
	{
		this->buffer = NULL;
		this->m_texture = NULL;
		this->nrOfVertices = 0;
		this->m_obb = NULL;
		this->m_bs = NULL;
		this->numSkeletons = 0;
		this->isAnimatied = false;
	}

	Mesh(ID3D10Buffer* _buffer, int _nrOfVertices)
	{
		this->buffer = _buffer;
		this->nrOfVertices = _nrOfVertices;
		this->m_obb = NULL;
		this->m_bs = NULL;
		this->numSkeletons = 0;
		this->isAnimatied = false;
	}
	~Mesh()
	{
		if(this->buffer)
			buffer->Release();
	}
};