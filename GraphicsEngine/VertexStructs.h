#ifndef VERTEX_STRUCTS_H
#define VERTEX_STRUCTS_H

#include "stdafx.h"

struct Vertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 texCoord;
	D3DXVECTOR3 normal;

	Vertex()
	{
		
	}

	Vertex(D3DXVECTOR3 _pos, D3DXVECTOR2 _texCoord, D3DXVECTOR3 _normal)
	{
		this->pos = _pos;
		this->texCoord = _texCoord;
		this->normal = _normal;
	}
};

#endif