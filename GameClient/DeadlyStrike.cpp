#include "DeadlyStrike.h"

DeadlyStrike::DeadlyStrike() : Skill(Skill::DEADLY_STRIKE, 0.0f)
{

}

DeadlyStrike::~DeadlyStrike()
{

}

bool DeadlyStrike::activate(unsigned int _targetId, unsigned int _senderId)
{
	int deadlyStrike = rand() % 100 + 1;
	bool triggered = false;

	UnitEntity *caster = (UnitEntity*)EntityHandler::getServerEntity(_senderId);
	UnitEntity *target = (UnitEntity*)EntityHandler::getServerEntity(_targetId);

	if(deadlyStrike < caster->getAgility() / 2 && target->getType() == ServerEntity::Type::EnemyType)
	{
		target->takeDamage(_senderId, INT_MAX, INT_MAX);
		EntityHandler::addEntity(new DelayedDamage(_senderId, _targetId, 0.5f, INT_MAX, INT_MAX, Skill::DEADLY_STRIKE));
		triggered = true;
	}

	return triggered;
}

void DeadlyStrike::updateSpecificSkill(float dt)
{

}

int DeadlyStrike::getCost()
{
	return DeadlyStrike::COST;
}