#pragma once

#include "stdafx.h"
#include "Mesh.h"

class DECLDIR Model
{
private:
	Mesh* m_mesh;
	D3DXMATRIX m_modelMatrix;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3 m_rotation;
public:
	Model();
	Model(Mesh* _mesh, D3DXVECTOR3 _position, D3DXVECTOR3 _scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3 _rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	~Model();
	
	D3DXVECTOR3 getPosition()const;
	D3DXVECTOR3 getScale()const;
	D3DXVECTOR3 getRotation()const;
	Mesh* getMesh()const;
	D3DXMATRIX getModelMatrix()const { return this->m_modelMatrix; }
	void setPosition(D3DXVECTOR3 _position);
	void setScale(D3DXVECTOR3 _scale);
	void setRotation(D3DXVECTOR3 _rotation);
	void updateModelMatrix();

	void setPosition(float x, float y, float z);
};