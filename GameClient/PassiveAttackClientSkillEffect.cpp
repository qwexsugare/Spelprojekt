#include "PassiveAttackClientSkillEffect.h"

PassiveAttackClientSkillEffect::PassiveAttackClientSkillEffect(unsigned int _masterId, unsigned int _skillId)
{
	m_lifeTime = 0;
	Entity* e = ClientEntityHandler::getEntity(_masterId);
	if(e != NULL)
	{
		if(e->m_model->getRightHand() != NULL)
		{
			switch(e->m_weapon)
			{
			case ModelIdHolder::MELEE:
				e->m_model->getAnimation()->Play("PassiveAbility_1H_Melee", false, 1);
				break;
			case ModelIdHolder::RANGED:
				e->m_model->getAnimation()->Play("PassiveAbility_1H_Range", false, 1);
				break;
			case ModelIdHolder::AOE:
				e->m_model->getAnimation()->Play("PassiveAbility_2H_Melee", false, 1);
				break;
			}
		}
		

		switch(_skillId)
		{
		case Skill::POISON_STRIKE:
			e->m_model->setGlowIndex("glowIntensity");
			break;
		case Skill::DEADLY_STRIKE:
			e->m_model->setGlowIndex("glowIntensity1");
			break;
		case Skill::LIFESTEALING_STRIKE:
			e->m_model->setGlowIndex("glowIntensity2");
			break;
		}
	}

}

PassiveAttackClientSkillEffect::~PassiveAttackClientSkillEffect()
{

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