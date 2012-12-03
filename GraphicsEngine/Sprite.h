#ifndef SPRITE_H
#define SPRITE_H

#include "stdafx.h"
#include "Mesh.h"
#include "VertexStructs.h"

class Sprite
{
private:
	ID3D10Buffer* m_buffer;
	int m_nrOfVertices;
	ID3D10ShaderResourceView* m_texture;	
	D3DXMATRIX m_modelMatrix;
public:
	Sprite(ID3D10Device *device, D3DXVECTOR2 position, D3DXVECTOR2 size,ID3D10ShaderResourceView *_texture);
	~Sprite();

	void setPosition(D3DXVECTOR2 position);
	void setSize(D3DXVECTOR2 size);
	void setRotation(float rotation);

	ID3D10Buffer *getBuffer();
	int getNrOfVertices();
	ID3D10ShaderResourceView *getTexture();
	D3DXMATRIX getModelMatrix();
};

#endif