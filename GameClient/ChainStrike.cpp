#include "ChainStrike.h"
#include "EntityHandler.h"
#include "ChainStrikeEffect.h"
#include "Hero.h"

const float ChainStrike::COOLDOWN = 12.0f;

ChainStrike::ChainStrike() : Skill(Skill::CHAIN_STRIKE, COOLDOWN)
{
	
}

ChainStrike::~ChainStrike()
{

}

bool ChainStrike::activate(unsigned int _targetId, unsigned int _senderId)
{
	ServerEntity* target = EntityHandler::getServerEntity(_targetId);
	if(target)
	{
		if(this->getCurrentCooldown() == 0 && (EntityHandler::getServerEntity(_senderId)->getPosition() - target->getPosition()).length() <= RANGE)
		{
			EntityHandler::addEntity(new ChainStrikeEffect(target->getId(), target->getPosition(), max(((Hero*)EntityHandler::getServerEntity(_senderId))->getWits()/2, 1)));
			this->resetCooldown();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void ChainStrike::updateSpecificSkill(float _dt)
{

}