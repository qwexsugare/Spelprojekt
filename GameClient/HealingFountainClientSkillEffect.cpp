#include "HealingFountainClientSkillEffect.h"

HealingFountainClientSkillEffect::HealingFountainClientSkillEffect(unsigned int _id)
{
	this->m_id = _id;
	this->m_lifetime = 1.0f;

	Entity *t = ClientEntityHandler::getEntity(_id);
	if(t != NULL)
	{
		m_heal = g_graphicsEngine->createParticleEngine("Heal", D3DXVECTOR4(0, 0, 0, 1), D3DXQUATERNION(0, 0, 0, 1), D3DXVECTOR2(1, 1));
	}
}

HealingFountainClientSkillEffect::~HealingFountainClientSkillEffect()
{
	Entity *t = ClientEntityHandler::getEntity(m_id);
	if(t != NULL)
	{
		g_graphicsEngine->removeParticleEngine(m_heal);
	}
}

void HealingFountainClientSkillEffect::update(float _dt)
{
	this->m_lifetime -= _dt;

	Entity *t = ClientEntityHandler::getEntity(m_id);
	if(m_heal != NULL && t != NULL)
	{
		if(m_lifetime >= 2)
		{
			m_heal->setAlive(false);
		}
		m_heal->setPosition(t->m_model->getPosition().toD3DXVector());
	}
}

bool HealingFountainClientSkillEffect::getActive()
{
	if(this->m_lifetime > 4.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}