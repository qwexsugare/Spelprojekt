#include "PassiveAttackClientSkillEffect.h"

PassiveAttackClientSkillEffect::PassiveAttackClientSkillEffect(unsigned int _masterId)
{
	Entity* e = ClientEntityHandler::getEntity(_masterId);

	if(e != NULL && e->m_model->getRightHand() != NULL)
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
}

PassiveAttackClientSkillEffect::~PassiveAttackClientSkillEffect()
{

}

void PassiveAttackClientSkillEffect::update(float dt)
{

}

bool PassiveAttackClientSkillEffect::getActive()
{
	return false;
}