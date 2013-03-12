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
		ServerEntity* caster = EntityHandler::getServerEntity(_senderId);
		if(caster)
		{
			if(this->getCurrentCooldown() == 0 && (caster->getPosition() - target->getPosition()).length() <= RANGE)
			{
				EntityHandler::addEntity(new ChainStrikeEffect(_targetId, max(((Hero*)caster)->getWits()/2, 1), START_DAMAGE, _senderId));
				this->resetCooldown();
				return true;
			}
			else
			{
				return false;
			}
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

void ChainStrike::updateSpecificSkill(float _dt)
{

}

int ChainStrike::getCost()
{
	return ChainStrike::COST;
}