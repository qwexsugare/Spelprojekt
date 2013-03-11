#include "HealingFountainClientSkillEffect.h"

HealingFountainClientSkillEffect::HealingFountainClientSkillEffect(unsigned int _id)
{
	this->m_id = _id;
	this->m_lifetime = 1.0f;

	//Här ska det vara partiklar
}

HealingFountainClientSkillEffect::~HealingFountainClientSkillEffect()
{

}

void HealingFountainClientSkillEffect::update(float _dt)
{
	this->m_lifetime -= _dt;
}

bool HealingFountainClientSkillEffect::getActive()
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