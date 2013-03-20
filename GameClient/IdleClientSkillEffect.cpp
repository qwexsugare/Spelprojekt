#include "IdleClientSkillEffect.h"

IdleClientSkillEffect::IdleClientSkillEffect(unsigned int masterId)
{
	Entity* master = ClientEntityHandler::getEntity(masterId);

	if(master != NULL && master->m_type == ServerEntity::HeroType)
	{
		if(master->m_weapon == ModelIdHolder::AOE)
		{
			master->m_model->getAnimation()->Stop("2Hrun");
			master->m_model->getAnimation()->PlayLoop("2Hidle");

		}
		else
		{
			master->m_model->getAnimation()->Stop("run");
			master->m_model->getAnimation()->PlayLoop("idle");
		}
	}
	else if(master != NULL && master->m_type == ServerEntity::EnemyType && master->m_subtype == Enemy::BOSS)
	{
		master->m_model->getAnimation()->Stop("run");
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