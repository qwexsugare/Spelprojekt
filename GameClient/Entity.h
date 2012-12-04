#pragma once

#include "Graphics.h"

struct Entity
{
	Model* m_model;

	Entity()
	{
		this->m_model = NULL;
	}

	Entity(Model* _model, FLOAT3 _position)
	{
		this->m_model = _model;
		this->m_model->setPosition(_position);
	}
};