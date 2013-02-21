#include "MeleeAttackClientSkillEffect.h"


MeleeAttackClientSkillEffect::MeleeAttackClientSkillEffect(unsigned int _masterId)
{
	this->m_lifetime = 1.0f;
	Entity* master = ClientEntityHandler::getEntity(_masterId);

	if(master != NULL)
	{
		master->m_model->getAnimation()->Play("attack");
	}
}

MeleeAttackClientSkillEffect::~MeleeAttackClientSkillEffect()
{

}

void MeleeAttackClientSkillEffect::update(float dt)
{
	this->m_lifetime -= dt;
}

bool MeleeAttackClientSkillEffect::getActive()
{
	if(this->m_lifetime <= 0.0f)
	{
		return false;
	}
	else
	{
		return true;
	}
}