#include "Teleport.h"
#include "EntityHandler.h"
#include "Hero.h"

const float Teleport::COOLDOWN = 1.0f;

Teleport::Teleport() : Skill(Skill::CLOUD_OF_DARKNESS, COOLDOWN)
{
	
}

Teleport::~Teleport()
{

}

bool Teleport::activate(FLOAT3 _position, unsigned int _senderId)
{
	ServerEntity* caster = EntityHandler::getServerEntity(_senderId);

	if(this->getCurrentCooldown() == 0 && (caster->getPosition() - _position).length() <= RANGE)
	{
		((Hero*)caster)->setNextPosition(((Hero*)caster)->getPosition());
		((Hero*)caster)->setPosition(_position);
		this->resetCooldown();
		return true;
	}
	else
		return false;
}

void Teleport::updateSpecificSkill(float _dt)
{

}