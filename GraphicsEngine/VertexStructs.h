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

struct SuperVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 texCoord;
	D3DXVECTOR3 normal;

	SuperVertex()
	{
		
	}

	SuperVertex(D3DXVECTOR3 _pos, D3DXVECTOR2 _texCoord, D3DXVECTOR3 _normal, D3DXVECTOR3 _tangent)
	{
		this->pos = _pos;
		this->texCoord = _texCoord;
		this->normal = _normal;
	}
};

struct AnimationVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 texCoord;
	D3DXVECTOR3 normal;
	D3DXVECTOR4 weight;
	D3DXVECTOR4 bone;

	AnimationVertex()
	{
		
	}

	AnimationVertex(D3DXVECTOR3 _pos, D3DXVECTOR2 _texCoord, D3DXVECTOR3 _normal, D3DXVECTOR3 _tangent, D3DXVECTOR4 _weight, D3DXVECTOR4 _bone)
	{
		this->pos = _pos;
		this->texCoord = _texCoord;
		this->normal = _normal;
		this->weight = _weight;
		this->bone = _bone;
	}
};

struct ChainVertex
{	
	D3DXVECTOR3 pos;
	D3DXVECTOR2 texCoord;
};
#endif