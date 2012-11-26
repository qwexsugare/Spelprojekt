#include "Model.h"

Model::Model()
{

}

Model::Model(Mesh* _mesh, D3DXVECTOR3 _position, D3DXVECTOR3 _scale, D3DXVECTOR3 _rotation)
{
	this->m_mesh = _mesh;
	this->m_position = _position;
	this->m_scale = _scale;
	this->m_rotation = _rotation;
	this->updateModelMatrix();
}

Model::~Model()
{

}

Mesh *Model::getMesh() const
{
	return this->m_mesh;
}

void Model::setPosition(D3DXVECTOR3 _position)
{
	this->m_position = _position;
	this->updateModelMatrix();
}

void Model::setScale(D3DXVECTOR3 _scale)
{
	this->m_scale = _scale;
	this->updateModelMatrix();
}

void Model::setRotation(D3DXVECTOR3 _rotation)
{
	this->m_rotation = _rotation;
	this->updateModelMatrix();
}

void Model::updateModelMatrix()
{
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, this->m_rotation.x, this->m_rotation.y, this->m_rotation.z);

	this->m_modelMatrix = D3DXMATRIX(
		this->m_scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, this->m_scale.y, 0.0f, 0.0f,
		0.0f, 0.0f, this->m_scale.z, 0.0f,
		this->m_position.x, this->m_position.y, this->m_position.z, 1.0f);

	D3DXMatrixMultiply(&this->m_modelMatrix, &this->m_modelMatrix, &rotationMatrix);
}

void Model::setPosition(float x, float y, float z)
{
	this->m_position = D3DXVECTOR3(x, y, z);
	this->updateModelMatrix();
}