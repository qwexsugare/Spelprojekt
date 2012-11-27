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
	Sprite(ID3D10Device *device, D3DXVECTOR2 position, D3DXVECTOR2 size,ID3D10Texture2D *_texture);
	~Sprite();

	Mesh *getMesh();
	ID3D10Texture2D *getTexture();

	void setPosition(D3DXVECTOR2 position);
	void setSize(D3DXVECTOR2 size);
	void setRotation(float rotation);
};

#endif