#include "EnigmaticPresence.h"
#include "EntityHandler.h"
#include "EnigmaticPresenceEffect.h"

EnigmaticPresence::EnigmaticPresence() : Skill(Skill::ENIGMATIC_PRESENCE, 0)
{
	
}

EnigmaticPresence::~EnigmaticPresence()
{

}

bool EnigmaticPresence::activate(unsigned int _senderId)
{
	ServerEntity* caster = EntityHandler::getServerEntity(_senderId);

	if(caster)
	{
		EntityHandler::addEntity(new EnigmaticPresenceEffect(_senderId));
	}

	return true;
}

void EnigmaticPresence::updateSpecificSkill(float _dt)
{

}