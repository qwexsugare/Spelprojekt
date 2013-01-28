#include "CloudOfDarkness.h"
#include "EntityHandler.h"
#include "CloudOfDarknessEffect.h"
#include "Hero.h"

const float CloudOfDarkness::COOLDOWN = 180.0f;

CloudOfDarkness::CloudOfDarkness() : Skill(Skill::CLOUD_OF_DARKNESS, COOLDOWN)
{
	
}

CloudOfDarkness::~CloudOfDarkness()
{

}

void CloudOfDarkness::activate(FLOAT3 _position, unsigned int _senderId)
{
	if(this->getCurrentCooldown() == 0 && (EntityHandler::getServerEntity(_senderId)->getPosition() - _position).length() <= RANGE)
	{
		EntityHandler::addEntity(new CloudOfDarknessEffect(_position, ((Hero*)EntityHandler::getServerEntity(_senderId))->getWits()*20));
		this->resetCooldown();
	}
}

void CloudOfDarkness::updateSpecificSkill(float _dt)
{

}