#include "StunningStrike.h"
#include "EntityHandler.h"
#include "StunningStrikeEffect.h"

const float StunningStrike::COOLDOWN = 120.0f;

StunningStrike::StunningStrike() : Skill(Skill::STUNNING_STRIKE, COOLDOWN)
{
	
}

StunningStrike::~StunningStrike()
{

}

bool StunningStrike::activate(unsigned int _senderId)
{
	if(this->getCurrentCooldown() == 0)
	{
		EntityHandler::addEntity(new StunningStrikeEffect(EntityHandler::getServerEntity(_senderId)->getPosition(), _senderId));
		this->resetCooldown();
		return true;
	}
	else
		return false;
}

void StunningStrike::updateSpecificSkill(float _dt)
{

}

int StunningStrike::getCost()
{
	return StunningStrike::COST;
}