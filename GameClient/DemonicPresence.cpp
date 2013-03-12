#include "DemonicPresence.h"
#include "EntityHandler.h"
#include "DemonicPresenceEffect.h"

const float DemonicPresence::COOLDOWN = 120.0f;

DemonicPresence::DemonicPresence() : Skill(Skill::DEMONIC_PRESENCE, COOLDOWN)
{
	
}

DemonicPresence::~DemonicPresence()
{

}

bool DemonicPresence::activate(unsigned int _senderId)
{
	if(this->getCurrentCooldown() == 0)
	{
		EntityHandler::addEntity(new DemonicPresenceEffect(_senderId));
		this->resetCooldown();
		return true;
	}
	else
		return false;
}

void DemonicPresence::updateSpecificSkill(float _dt)
{

}

int DemonicPresence::getCost()
{
	return DemonicPresence::COST;
}