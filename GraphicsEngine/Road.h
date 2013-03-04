#pragma once

#include "stdafx.h"
#include "ResourceHolder.h"
#include <DirectXMath.h>
#include <DirectXCollision.h>

class Road
{
private:
	ID3D10Buffer* m_vertexBuffer;
	int m_nrOfVertices;
	D3DXMATRIX m_modelMatrix;
	ID3D10ShaderResourceView* m_texture;
	BoundingOrientedBox* m_obb;
public:
	static const int SIZE = 1;

	Road();
	Road(ID3D10Device* _device, ID3D10ShaderResourceView* _texture, D3DXVECTOR3 _pos, float _rot, float _scale);
	~Road();
	
	const D3DXMATRIX& getModelMatrix()const { return m_modelMatrix; }
	ID3D10ShaderResourceView* getTexture()const { return m_texture; }
 	int getNrOfVertices()const { return this->m_nrOfVertices; }
	ID3D10Buffer* getVertexBuffer()const { return this->m_vertexBuffer; }

	BoundingOrientedBox* getOBB()const { return this->m_obb; }
	D3DXVECTOR2 getPosition2D();
	D3DXVECTOR3 getPosition();
};

