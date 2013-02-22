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
	UnitEntity* caster = (UnitEntity*)EntityHandler::getServerEntity(_senderId);

	if(caster != NULL)
	{
		EntityHandler::addEntity(new DelayedDamage(_senderId, _targetId, 0.5f, caster->getPhysicalDamage(), caster->getMentalDamage(), Skill::RANGED_ATTACK));
	}

	return true;
}

void RangedAttack::updateSpecificSkill(float dt)
{

}