#include "CloudOfDarkness.h"
#include "EntityHandler.h"
#include "CloudOfDarknessEffect.h"
#include "Hero.h"

const float CloudOfDarkness::COOLDOWN = 180.0f;

CloudOfDarkness::CloudOfDarkness() : Skill(Skill::CLOUD_OF_DARKNESS, 0.0f)
{
	
}

CloudOfDarkness::~CloudOfDarkness()
{

}

void CloudOfDarkness::activate(unsigned int _targetId, unsigned int _senderId)
{
	ServerEntity* target = EntityHandler::getServerEntity(_targetId);
	if(target)
	{
		if(this->getCooldown() == 0 && (EntityHandler::getServerEntity(_senderId)->getPosition() - target->getPosition()).length() < RANGE)
		{
			EntityHandler::addEntity(new CloudOfDarknessEffect(target->getId(), target->getPosition(), max(((Hero*)EntityHandler::getServerEntity(_senderId))->getWits()/2, 1)));
			this->setCooldown(COOLDOWN);
		}
	}
}

void CloudOfDarkness::updateSpecificSkill(float _dt)
{

}