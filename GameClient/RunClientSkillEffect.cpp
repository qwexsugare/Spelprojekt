#include "RunClientSkillEffect.h"

RunClientSkillEffect::RunClientSkillEffect(unsigned int masterId)
{
	Entity* master = ClientEntityHandler::getEntity(masterId);

	if(master != NULL && master->m_type == ServerEntity::HeroType)
	{
		if(master->m_weapon == ModelIdHolder::AOE)
		{
			master->m_model->getAnimation()->Stop("2Hidle");
			master->m_model->getAnimation()->PlayLoop("2Hrun", -1, master->movementSpeed / 2);

		}
		else
		{
			master->m_model->getAnimation()->Stop("idle");
			master->m_model->getAnimation()->PlayLoop("run", -1, master->movementSpeed / 2);
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