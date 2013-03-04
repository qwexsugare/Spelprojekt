#include "SwiftAsACatPowerfulAsABoarClientSkillEffect.h"

SwiftAsACatPowerfulAsABoarClientSkillEffect::SwiftAsACatPowerfulAsABoarClientSkillEffect(unsigned int _masterId)
{
	Entity *e = ClientEntityHandler::getEntity(_masterId);

	if(e != NULL)
	{
		if(e->m_weapon == ModelIdHolder::WEAPON_TYPE::AOE)
		{
			e->m_model->getAnimation()->Play("SwiftAsButterfly2Hand");
		}
		else
		{
			e->m_model->getAnimation()->Play("SwiftAsButterfly_1H");
		}
	}
}

SwiftAsACatPowerfulAsABoarClientSkillEffect::~SwiftAsACatPowerfulAsABoarClientSkillEffect()
{

}

void SwiftAsACatPowerfulAsABoarClientSkillEffect::update(float _dt)
{

}

bool SwiftAsACatPowerfulAsABoarClientSkillEffect::getActive()
{
	return false;
}