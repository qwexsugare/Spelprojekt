#pragma once

#include "Graphics.h"
#include "ServerEntity.h"

struct Entity
{
	unsigned int m_id;
	unsigned int m_health;
	Model* m_model;
	ServerEntity::Type m_type;

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