#include "IdleClientSkillEffect.h"

IdleClientSkillEffect::IdleClientSkillEffect(unsigned int masterId)
{
	Entity* master = ClientEntityHandler::getEntity(masterId);

	if(master != NULL)
	{
		if(master->m_twoHandedWeapon == false)
		{
			master->m_model->getAnimation()->Stop("run");
			master->m_model->getAnimation()->PlayLoop("idle");
		}
		else
		{
			master->m_model->getAnimation()->Stop("2Hrun");
			master->m_model->getAnimation()->PlayLoop("2Hidle");
		}
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