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
	bool triggered = false;

	if(lifesteal < LifestealingStrike::LIFE_STEAL_CHANCE)
	{
		caster->heal(caster->getPhysicalDamage() * 0.5f);
		caster->getMessageQueue()->pushOutgoingMessage(new CreateActionMessage(Skill::LIFESTEALING_STRIKE, _senderId, caster->getPosition()));
		triggered = true;
	}

	return triggered;
}

void LifestealingStrike::updateSpecificSkill(float dt)
{

}