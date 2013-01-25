#include "StunningStrike.h"
#include "EntityHandler.h"
#include "StunningStrikeEffect.h"
#include "Hero.h"

const float StunningStrike::COOLDOWN = 1.0f;

StunningStrike::StunningStrike() : Skill(Skill::CLOUD_OF_DARKNESS, 0.0f)
{
	
}

StunningStrike::~StunningStrike()
{

}

void StunningStrike::activate(FLOAT3 _position, unsigned int _senderId)
{
	if(this->getCooldown() == 0 && (EntityHandler::getServerEntity(_senderId)->getPosition() - _position).length() < RANGE)
	{
		EntityHandler::addEntity(new StunningStrikeEffect(_position, ((Hero*)EntityHandler::getServerEntity(_senderId))->getWits()*20));
		this->setCooldown(COOLDOWN);
	}
}

void StunningStrike::updateSpecificSkill(float _dt)
{

}