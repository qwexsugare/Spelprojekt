#include "PoisonStrike.h"

PoisonStrike::PoisonStrike() : Skill(Skill::POISON_STRIKE, 0.0f)
{

}

PoisonStrike::~PoisonStrike()
{

}

bool PoisonStrike::activate(unsigned int _targetId, unsigned int _senderId)
{
	int poison = rand() % 100 + 1;
	bool triggered = false;

	UnitEntity *caster = (UnitEntity*)EntityHandler::getServerEntity(_senderId);
	UnitEntity *target = (UnitEntity*)EntityHandler::getServerEntity(_targetId);

	if(poison < PoisonStrike::POISON_STRIKE_CHANCE)
	{
		if(target->getPoisonCounter() < 4)
		{
			target->setPoisonCounter(target->getPoisonCounter() + 1);
		}

		EntityHandler::addEntity(new DelayedDamage(_senderId, _targetId, 0.5f, 0,  target->getPoisonCounter() * 5, Skill::POISON_STRIKE));
		triggered = true;
	}

	return triggered;
}

void PoisonStrike::updateSpecificSkill(float dt)
{

}