#include "CloudOfDarkness.h"
#include "EntityHandler.h"
#include "CloudOfDarknessEffect.h"
#include "Hero.h"

const float CloudOfDarkness::COOLDOWN = 90.0f;

CloudOfDarkness::CloudOfDarkness() : Skill(Skill::CLOUD_OF_DARKNESS, COOLDOWN)
{
	
}

CloudOfDarkness::~CloudOfDarkness()
{

}

bool CloudOfDarkness::activate(FLOAT3 _position, unsigned int _senderId)
{
	if(this->getCurrentCooldown() == 0 && (EntityHandler::getServerEntity(_senderId)->getPosition() - _position).length() <= RANGE)
	{
		EntityHandler::addEntity(new CloudOfDarknessEffect(_position, ((Hero*)EntityHandler::getServerEntity(_senderId))->getWits()*20, _senderId));
		this->resetCooldown();

		return true;
	}
	else
		return false;
}

void CloudOfDarkness::updateSpecificSkill(float _dt)
{

}

int CloudOfDarkness::getCost()
{
	return CloudOfDarkness::COST;
}