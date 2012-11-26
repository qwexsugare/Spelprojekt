#include "Model.h"

Model::Model()
{

}

Model::Model(Mesh* _mesh)
{

}

Model::~Model()
{

}

Mesh *Model::getMesh() const
{
	return this->m_mesh;
}