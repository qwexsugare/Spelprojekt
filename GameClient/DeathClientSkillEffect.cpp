#include "DeathClientSkillEffect.h"

DeathClientSkillEffect::DeathClientSkillEffect(unsigned int _masterId)
{
	this->m_masterId = _masterId;
	this->m_lifetime = 5.0f;

	Entity *e = ClientEntityHandler::getEntity(this->m_masterId);

	if(e != NULL)
	{
		this->m_model = g_graphicsEngine->createModel(e->m_model, false);
		this->m_model->getAnimation()->Play("death", true);
		
		if(this->m_model->getObb() == NULL)
		{
			this->m_lifetime = this->m_lifetime + this->m_model->getBs()->Radius;
		}
		else if(this->m_model->getBs() == NULL)
		{
			this->m_lifetime = this->m_lifetime + this->m_model->getObb()->Extents.y;
		}
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
		FLOAT3 pos = this->m_model->getPosition();
		pos.y = pos.y - dt * this->m_lifetime;
		this->m_model->setPosition(pos);
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