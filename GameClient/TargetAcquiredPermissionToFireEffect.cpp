#include "TargetAcquiredPermissionToFireEffect.h"

TargetAcquiredPermissionToFireEffect::TargetAcquiredPermissionToFireEffect(FLOAT3 _position)
{
	this->m_position = _position;
	this->m_lifetime = 5.0f;

	//Turn off all towers
	vector<ServerEntity*> turrets = EntityHandler::getEntitiesByType(ServerEntity::TowerType);

	for(int i = 0; i < turrets.size(); i++)
	{
		((Turret*)turrets[i])->setActive(false);
	}
}

TargetAcquiredPermissionToFireEffect::~TargetAcquiredPermissionToFireEffect()
{
	//Reactivate all the towers
	vector<ServerEntity*> turrets = EntityHandler::getEntitiesByType(ServerEntity::TowerType);

	for(int i = 0; i < turrets.size(); i++)
	{
		((Turret*)turrets[i])->setActive(true);
	}
}

void TargetAcquiredPermissionToFireEffect::update(float _dt)
{
	this->m_lifetime = this->m_lifetime - _dt;

	//Gör skada inom ett område?

	if(this->m_lifetime <= 0.0f)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}