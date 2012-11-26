#pragma once

#include "stdafx.h"

struct Mesh
{
	ID3D10Buffer* buffer;
	int nrOfVertices;
	ID3D10ShaderResourceView* m_texture;

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