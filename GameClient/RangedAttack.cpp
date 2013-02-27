#include "RangedAttack.h"

const float RangedAttack::RANGE = 5.0f;

RangedAttack::RangedAttack() : Skill(Skill::RANGED_ATTACK, 0.0f)
{
	this->setRange(RangedAttack::RANGE);
}

RangedAttack::~RangedAttack()
{

}

bool RangedAttack::activate(unsigned int _targetId, unsigned int _senderId)
{
	bool ret;

	ServerEntity* target = EntityHandler::getServerEntity(_targetId);
	if(target)
	{
		ServerEntity* caster = EntityHandler::getServerEntity(_senderId);
		if(caster)
		{
			float timeToImpact = (target->getPosition() - caster->getPosition()).length()/VELOCITY;

			EntityHandler::addEntity(new DelayedDamage(
				_senderId, _targetId, timeToImpact, ((UnitEntity*)caster)->getPhysicalDamage(), ((UnitEntity*)caster)->getMentalDamage(), Skill::RANGED_ATTACK));

			ret = true;
		}
		else
			ret = false;
	}
	else
		ret = false;

	return ret;
}

void RangedAttack::updateSpecificSkill(float dt)
{

}