#include "MeleeAOEAttack.h"

const float MeleeAOEAttack::RANGE = 2.0f;

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
			if(entities[i]->getType() == target->getType() && (entities[i]->getPosition() - caster->getPosition()).length() <= this->getRange())
			{
				EntityHandler::addEntity(new DelayedDamage(_senderId, entities[i]->getId(), 0.5f, caster->getPhysicalDamage(), caster->getMentalDamage(), Skill::AOE_MELEE_ATTACK));
			}
		}
	}

	return true;
}

void MeleeAOEAttack::updateSpecificSkill(float dt)
{

}