#ifndef SPRITE_BASE_H
#define SPRITE_BASE_H

#include "stdafx.h"

class SpriteBase
{
public:
	SpriteBase()
	{

	}

	virtual void update(float dt) = 0;

	virtual ID3D10Buffer *getBuffer() = 0;
	virtual ID3D10ShaderResourceView *getTexture() = 0;
	virtual D3DXMATRIX getModelMatrix() = 0;
	virtual int getStartIndex() = 0;
	virtual int getNrOfVertices() = 0;
	virtual int getLayer() = 0;
	virtual bool getVisible() = 0;
};

#endif