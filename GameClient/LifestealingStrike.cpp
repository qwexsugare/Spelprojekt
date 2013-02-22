#include "LifestealingStrike.h"

LifestealingStrike::LifestealingStrike() : Skill(Skill::LIFESTEALING_STRIKE, 0.0f)
{

}

LifestealingStrike::~LifestealingStrike()
{

}

bool LifestealingStrike::activate(unsigned int _targetId, unsigned int _senderId)
{
	int lifesteal = rand() % 100 + 1;
	UnitEntity *caster = (UnitEntity*)EntityHandler::getServerEntity(_senderId);

	if(lifesteal < LifestealingStrike::LIFE_STEAL_CHANCE)
	{
		caster->heal(caster->getPhysicalDamage() * 0.5f);
	}

	return true;
}

void LifestealingStrike::updateSpecificSkill(float dt)
{

}