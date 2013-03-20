#include "PassiveAttackClientSkillEffect.h"

PassiveAttackClientSkillEffect::PassiveAttackClientSkillEffect(unsigned int _masterId, unsigned int _skillId)
{
	m_lifeTime = 0;
	m_masterID = _masterId;
	m_master = ClientEntityHandler::getEntity(_masterId);
	if(m_master != NULL)
	{
		if(m_master->m_model->getRightHand() != NULL)
		{
			switch(m_master->m_weapon)
			{
			case ModelIdHolder::MELEE:
				m_master->m_model->getAnimation()->Play("PassiveAbility_1H_Melee", false, 1);
				break;
			case ModelIdHolder::RANGED:
				m_master->m_model->getAnimation()->Play("PassiveAbility_1H_Range", false, 1);
				break;
			case ModelIdHolder::AOE:
				m_master->m_model->getAnimation()->Play("PassiveAbility_2H_Melee", false, 1);
				break;
			}
		}
		

		switch(_skillId)
		{
		case Skill::POISON_STRIKE:
			m_master->m_model->setWeaponGlowIndex("glowIntensity");
			break;
		case Skill::DEADLY_STRIKE:
			m_master->m_model->setWeaponGlowIndex("glowIntensity1");
			break;
		}
	}

}

PassiveAttackClientSkillEffect::~PassiveAttackClientSkillEffect()
{
	m_master = ClientEntityHandler::getEntity(m_masterID);
	if(m_master != NULL)
		m_master->m_model->setWeaponGlowIndex("glowIntensity3");
}

void PassiveAttackClientSkillEffect::update(float dt)
{
	m_lifeTime += dt;
}

bool PassiveAttackClientSkillEffect::getActive()
{
	if(m_lifeTime >= 1.0f)
		return false;
	else
		return true;
}