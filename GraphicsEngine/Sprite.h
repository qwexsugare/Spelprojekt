#ifndef SPRITE_H
#define SPRITE_H

#include "stdafx.h"
#include "Mesh.h"
#include "VertexStructs.h"

class Sprite
{
private:
	Mesh *m_mesh;
	ID3D10Texture2D *m_texture;
public:
	Sprite(ID3D10Device *device, D3DXVECTOR2 position, D3DXVECTOR2 v1, D3DXVECTOR2 v2,ID3D10Texture2D *m_texture);
	~Sprite();

	Mesh *getMesh();
	ID3D10Texture2D *getTexture();
};

#endif