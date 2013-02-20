#include "IdleClientSkillEffect.h"

IdleClientSkillEffect::IdleClientSkillEffect(unsigned int masterId)
{
	Entity* master = ClientEntityHandler::getEntity(masterId);

	if(master != NULL)
	{
		master->m_model->getAnimation()->PlayLoop("idle");
	}
}

IdleClientSkillEffect::~IdleClientSkillEffect()
{

}

void IdleClientSkillEffect::update(float dt)
{

}

bool IdleClientSkillEffect::getActive()
{
	return false;
}