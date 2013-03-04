#include "RunClientSkillEffect.h"

RunClientSkillEffect::RunClientSkillEffect(unsigned int masterId)
{
	Entity* master = ClientEntityHandler::getEntity(masterId);

	if(master != NULL)
	{
		if(master->m_weapon == ModelIdHolder::AOE)
		{
			master->m_model->getAnimation()->Stop("2Hidle");
			master->m_model->getAnimation()->PlayLoop("2Hrun");

		}
		else
		{
			master->m_model->getAnimation()->Stop("idle");
			master->m_model->getAnimation()->PlayLoop("run");
		}
	}
}

RunClientSkillEffect::~RunClientSkillEffect()
{

}

void RunClientSkillEffect::update(float dt)
{

}

bool RunClientSkillEffect::getActive()
{
	return false;
}