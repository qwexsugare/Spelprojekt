#include "DeathClientSkillEffect.h"

DeathClientSkillEffect::DeathClientSkillEffect(unsigned int _masterId, FLOAT3 _position)
{
	this->m_masterId = _masterId;
	this->m_lifetime = 10.0f;
	this->m_sink = false;

	Entity *e = ClientEntityHandler::getEntity(this->m_masterId);

	if(e->m_type == ServerEntity::EnemyType)
	{
		this->m_sink = true;
	}

	if(e != NULL)
	{
		this->m_model = g_graphicsEngine->createModel(e->m_model, false);
		this->m_model->setPosition(_position);
		this->m_model->getAnimation()->Play("death", true);
	}
}

DeathClientSkillEffect::~DeathClientSkillEffect()
{

}

void DeathClientSkillEffect::update(float dt)
{
	this->m_lifetime = this->m_lifetime - dt;

	if(this->m_lifetime < 5.0f)
	{
		if(this->m_sink == true)
		{
			FLOAT3 pos = this->m_model->getPosition();
			pos.y = pos.y - dt;
			this->m_model->setPosition(pos);
		}
	}
}

bool DeathClientSkillEffect::getActive()
{
	if(this->m_lifetime <= 0.0f)
	{
		g_graphicsEngine->removeModel(this->m_model);
		return false;
	}
	else
	{
		return true;
	}
}