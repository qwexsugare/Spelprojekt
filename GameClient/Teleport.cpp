#include "Teleport.h"
#include "EntityHandler.h"
#include "Hero.h"
#include "TeleportEffect.h"

const float Teleport::COOLDOWN = 30.0f;

Teleport::Teleport() : Skill(Skill::TELEPORT, COOLDOWN)
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
		((Hero*)caster)->setPosition(_position);
		((Hero*)caster)->setNextPosition(((Hero*)caster)->getPosition());
		this->resetCooldown();
		EntityHandler::addEntity(new TeleportEffect(_senderId));
		return true;
	}
	else
		return false;
}

void Teleport::updateSpecificSkill(float _dt)
{

}