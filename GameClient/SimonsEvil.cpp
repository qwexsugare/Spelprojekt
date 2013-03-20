#include "SimonsEvil.h"
#include "EntityHandler.h"
#include "SimonsEvilEffect.h"

const float SimonsEvil::COOLDOWN = 40.0f;

SimonsEvil::SimonsEvil() : Skill(Skill::SIMONS_EVIL, COOLDOWN)
{
	
}

SimonsEvil::~SimonsEvil()
{

}

bool SimonsEvil::activate(unsigned int _senderId)
{
	if(this->getCurrentCooldown() == 0)
	{
		EntityHandler::addEntity(new SimonsEvilEffect(_senderId));
		this->resetCooldown();

		return true;
	}
	else
		return false;
}

void SimonsEvil::updateSpecificSkill(float _dt)
{

}