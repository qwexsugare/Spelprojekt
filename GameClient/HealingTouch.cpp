#include "HealingTouch.h"
#include "EntityHandler.h"
#include "Hero.h"

const float HealingTouch::COOLDOWN = 10.0f;

HealingTouch::HealingTouch() : Skill(Skill::HEALING_TOUCH, COOLDOWN)
{
	
}

HealingTouch::~HealingTouch()
{

}

bool HealingTouch::activate(unsigned int _targetId, unsigned int _senderId)
{
	ServerEntity* caster = EntityHandler::getServerEntity(_senderId);
	ServerEntity* target = EntityHandler::getServerEntity(_targetId);

	if(caster && target)
	{
		if(this->getCurrentCooldown() == 0 && (caster->getPosition() - target->getPosition()).length() <= RANGE)
		{
			((Hero*)target)->heal(((Hero*)caster)->getWits()*15);
			caster->getMessageQueue()->pushOutgoingMessage(new CreateActionTargetMessage(Skill::HEALING_TOUCH, _senderId, _targetId, caster->getPosition()));
			this->resetCooldown();
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

void HealingTouch::updateSpecificSkill(float _dt)
{

}

int HealingTouch::getCost()
{
	return HealingTouch::COST;
}