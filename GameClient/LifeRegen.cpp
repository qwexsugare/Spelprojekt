#include "LifeRegen.h"
#include "EntityHandler.h"
#include "LifeRegenEffect.h"

LifeRegen::LifeRegen() : Skill(Skill::LIFE_REGEN, 0)
{
	
}

LifeRegen::~LifeRegen()
{

}

bool LifeRegen::activate(unsigned int _senderId)
{
	ServerEntity* caster = EntityHandler::getServerEntity(_senderId);

	if(caster)
	{
		EntityHandler::addEntity(new LifeRegenEffect(_senderId));
	}

	return true;
}

void LifeRegen::updateSpecificSkill(float _dt)
{

}