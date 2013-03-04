#include "TargetAcquiredClientSkillEffect.h"

TargetAcquiredClientSkillEffect::TargetAcquiredClientSkillEffect(unsigned int _masterId, FLOAT3 position)
{
	this->m_model = g_graphicsEngine->createModel("CloudOfDarkness", position);
}

TargetAcquiredClientSkillEffect::~TargetAcquiredClientSkillEffect()
{
	g_graphicsEngine->removeModel(this->m_model);
}

void TargetAcquiredClientSkillEffect::update(float _dt)
{
	this->m_lifetime = this->m_lifetime - _dt;
}

bool TargetAcquiredClientSkillEffect::getActive()
{
	if(this->m_lifetime > 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}