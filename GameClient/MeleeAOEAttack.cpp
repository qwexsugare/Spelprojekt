#include "MeleeAOEAttack.h"

const float MeleeAOEAttack::RANGE = 1.0f;
const float MeleeAOEAttack::AOE_RANGE = 2.0f;

MeleeAOEAttack::MeleeAOEAttack()
{
	this->setRange(MeleeAOEAttack::RANGE);
}

MeleeAOEAttack::~MeleeAOEAttack()
{

}

bool MeleeAOEAttack::activate(unsigned int _targetId, unsigned int _senderId)
{
	UnitEntity* caster = (UnitEntity*)EntityHandler::getServerEntity(_senderId);
	UnitEntity* target = (UnitEntity*)EntityHandler::getServerEntity(_targetId);

	if(caster != NULL && target != NULL)
	{
		vector<ServerEntity*> entities = EntityHandler::getEntities();

		for(int i = 0; i < entities.size(); i++)
		{
			if(entities[i]->getType() == target->getType() && (entities[i]->getPosition() - caster->getPosition()).length() <= MeleeAOEAttack::AOE_RANGE)
			{
				EntityHandler::addEntity(new DelayedDamage(_senderId, entities[i]->getId(), caster->getAttackSpeed() / 2, caster->getPhysicalDamage(), caster->getMentalDamage(), Skill::AOE_MELEE_ATTACK, 2.0f / caster->getAttackSpeed()));
			}
		}
	}

	return true;
}

void MeleeAOEAttack::updateSpecificSkill(float dt)
{

}