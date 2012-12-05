#ifndef SPRITE_H
#define SPRITE_H

#include "stdafx.h"
#include "SpriteBase.h"
#include "Mesh.h"
#include "VertexStructs.h"
#include "DeviceHandler.h"
#include "DataStructures.h"

class Sprite : public SpriteBase
{
private:
	DeviceHandler *m_deviceHandler;
	ID3D10Buffer* m_buffer;
	int m_nrOfVertices;
	ID3D10ShaderResourceView* m_texture;	
	D3DXMATRIX m_modelMatrix;
	int m_layer;
public:
	Sprite(DeviceHandler *_deviceHandler, FLOAT2 position, FLOAT2 size,ID3D10ShaderResourceView *_texture, int _layer);
	~Sprite();

	DECLDIR void setPosition(FLOAT2 position);
	DECLDIR void setSize(FLOAT2 size);
	DECLDIR void setRotation(float rotation);

	ID3D10Buffer *getBuffer();
	int getNrOfVertices();
	int getStartIndex();
	ID3D10ShaderResourceView *getTexture();
	D3DXMATRIX getModelMatrix();
	int getLayer();

	void update(float dt);
};

#endif