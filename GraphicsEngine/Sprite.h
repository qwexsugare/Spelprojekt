#ifndef SPRITE_H
#define SPRITE_H

#include "stdafx.h"
#include "Mesh.h"
#include "VertexStructs.h"
#include "DeviceHandler.h"
#include "DataStructures.h"

class Sprite
{
private:
	DeviceHandler *m_deviceHandler;
	ID3D10Buffer* m_buffer;
	int m_nrOfVertices;
	ID3D10ShaderResourceView* m_texture;	
	D3DXMATRIX m_modelMatrix;
public:
	Sprite(DeviceHandler *_deviceHandler, FLOAT2 position, FLOAT2 size,ID3D10ShaderResourceView *_texture);
	~Sprite();

	DECLDIR void setPosition(FLOAT2 position);
	DECLDIR void setSize(FLOAT2 size);
	DECLDIR void setRotation(float rotation);

	ID3D10Buffer *getBuffer();
	int getNrOfVertices();
	ID3D10ShaderResourceView *getTexture();
	D3DXMATRIX getModelMatrix();
};

#endif