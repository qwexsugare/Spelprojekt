#include "MeleeAttack.h"

const float MeleeAttack::RANGE = 1.0f;

MeleeAttack::MeleeAttack() : Skill(Skill::MELEE_ATTACK, 0.0f)
{
	this->setRange(MeleeAttack::RANGE);
}

MeleeAttack::~MeleeAttack()
{

}

bool MeleeAttack::activate(unsigned int _targetId, unsigned int _senderId)
{
	UnitEntity* caster = (UnitEntity*)EntityHandler::getServerEntity(_senderId);

	if(caster != NULL)
	{
		EntityHandler::addEntity(new DelayedDamage(_senderId, _targetId, caster->getAttackSpeed() / 2, max((float)caster->getStrength(), caster->getPhysicalDamage()), max((float)caster->getWits(), caster->getMentalDamage()), Skill::MELEE_ATTACK, 2.0f / caster->getAttackSpeed()));
	}

	return true;
}

void MeleeAttack::updateSpecificSkill(float dt)
{

}