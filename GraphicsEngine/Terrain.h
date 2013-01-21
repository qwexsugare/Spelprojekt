#pragma once

#include "stdafx.h"
#include "DataStructures.h"

class Terrain
{
private:
	float m_width;
	float m_height;
	int m_rows;
	int m_cols;
	int m_nrOfVertices;
	int m_nrOfTextures;
	ID3D10ShaderResourceView** m_textures;
	int m_nrOfBlendMaps;
	ID3D10ShaderResourceView** m_blendMaps;
	D3DXVECTOR3 m_topLeft;
	D3DXVECTOR3 m_bottomRight;
	ID3D10Buffer* m_vertexBuffer;
	D3DXMATRIX m_modelMatrix;
public:
	Terrain();
	Terrain(ID3D10Device* _device, D3DXVECTOR3 v1, D3DXVECTOR3 v2, int rows, int cols, ID3D10ShaderResourceView** _textures, int _nrOfTextures, ID3D10ShaderResourceView** _blendMaps, int _nrOfBlendMaps);
	virtual ~Terrain();
	
	ID3D10ShaderResourceView** getBlendMaps()const { return this->m_blendMaps; }
	FLOAT2 getBottomRightCorner()const { return FLOAT2(m_bottomRight.x, m_bottomRight.z); }
	float getHeight()const { return m_height; }
	D3DXMATRIX getModelMatrix()const { return this->m_modelMatrix; }
	int getNrOfBlendMaps()const { return this->m_nrOfBlendMaps; }
	int getNrOfTextures()const { return this->m_nrOfTextures; }
	int getNrOfVertices()const { return this->m_nrOfVertices; }
	FLOAT2 getTopLeftCorner()const { return FLOAT2(m_topLeft.x, m_topLeft.z); }
	ID3D10Buffer* getVertexBuffer()const { return this->m_vertexBuffer; }
	float getWidth()const { return m_width; }
	ID3D10ShaderResourceView** getTextures()const { return this->m_textures; }
};