#include "StunningStrike.h"
#include "EntityHandler.h"
#include "StunningStrikeEffect.h"

const float StunningStrike::COOLDOWN = 120.0f;

StunningStrike::StunningStrike() : Skill(Skill::STUNNING_STRIKE, 0.0f)
{
	
}

StunningStrike::~StunningStrike()
{

}

void StunningStrike::activate(unsigned int _senderId)
{
	if(this->getCooldown() == 0)
	{
		EntityHandler::addEntity(new StunningStrikeEffect(EntityHandler::getServerEntity(_senderId)->getPosition()));
		this->setCooldown(COOLDOWN);
	}
}

void StunningStrike::updateSpecificSkill(float _dt)
{

}