#pragma once

#include "Graphics.h"

struct Entity
{
	unsigned int m_id;
	Model* m_model;

	Entity()
	{
		this->m_model = NULL;
	}

	Entity(Model* _model, unsigned int _id)
	{
		this->m_model = _model;
		this->m_id = _id;
	}
};