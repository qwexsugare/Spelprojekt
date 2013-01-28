#include "StunningStrike.h"
#include "EntityHandler.h"
#include "StunningStrikeEffect.h"

const float StunningStrike::COOLDOWN = 1.0f;

StunningStrike::StunningStrike() : Skill(Skill::STUNNING_STRIKE, COOLDOWN)
{
	
}

StunningStrike::~StunningStrike()
{

}

void StunningStrike::activate(unsigned int _senderId)
{
	if(this->getCurrentCooldown() == 0)
	{
		EntityHandler::addEntity(new StunningStrikeEffect(EntityHandler::getServerEntity(_senderId)->getPosition()));
		this->resetCooldown();
	}
}

void StunningStrike::updateSpecificSkill(float _dt)
{

}