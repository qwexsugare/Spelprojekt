#pragma once

#include "stdafx.h"

struct SubMesh
{
	ID3D10Buffer* buffer;
	map<string, ID3D10ShaderResourceView*> textures;
	int skeletonId;
	int numInfluences;
	int numVerts;
	int materialId;
	string name;

	SubMesh(ID3D10Buffer* _buffer, int _nrOfVertices)
	{
		this->buffer = _buffer;
		this->numVerts = _nrOfVertices;
	}
	~SubMesh()
	{
		if(buffer)
			buffer->Release();
		map<string, ID3D10ShaderResourceView*>::const_iterator itr;
		for(itr = textures.begin(); itr != textures.end(); ++itr)
		{
			if(itr->second)
				itr->second->Release();
		}
	}
}; 