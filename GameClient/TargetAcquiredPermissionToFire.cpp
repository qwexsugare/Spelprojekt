#include "TargetAcquiredPermissionToFire.h"

const float TargetAcquiredPermissionToFire::COOLDOWN = 180.0f;

TargetAcquiredPermissionToFire::TargetAcquiredPermissionToFire() : Skill(Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE, TargetAcquiredPermissionToFire::COOLDOWN)
{

}

TargetAcquiredPermissionToFire::~TargetAcquiredPermissionToFire()
{

}

bool TargetAcquiredPermissionToFire::activate(FLOAT3 _position, unsigned int _senderId)
{
	if(this->getCurrentCooldown() == 0)
	{
		EntityHandler::addEntity(new TargetAcquiredPermissionToFireEffect(_position));
		this->resetCooldown();
		return true;
	}
	else
	{
		return false;
	}
}

void TargetAcquiredPermissionToFire::updateSpecificSkill(float _dt)
{

}