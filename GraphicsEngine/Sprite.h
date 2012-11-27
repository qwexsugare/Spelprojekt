#ifndef SPRITE_H
#define SPRITE_H

#include "stdafx.h"
#include "Mesh.h"
#include "VertexStructs.h"

class Sprite
{
private:
	LPD3DX10SPRITE *m_sprite;
public:
	Sprite(ID3D10Device *device, D3DXVECTOR2 position, D3DXVECTOR2 size,ID3D10Texture2D *_texture);
	~Sprite();

	D3DX10_SPRITE *getSprite();

	void setPosition(D3DXVECTOR2 position);
	void setSize(D3DXVECTOR2 size);
	void setRotation(float rotation);
};

#endif