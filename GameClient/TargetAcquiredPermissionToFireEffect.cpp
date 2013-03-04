#include "TargetAcquiredPermissionToFireEffect.h"

const float TargetAcquiredPermissionToFireEffect::RANGE = 2.0f;
const float TargetAcquiredPermissionToFireEffect::LIFETIME = 5.0f;

TargetAcquiredPermissionToFireEffect::TargetAcquiredPermissionToFireEffect(unsigned int _casterId, FLOAT3 _position)
{
	this->m_position = _position;
	this->m_lifetime = TargetAcquiredPermissionToFireEffect::LIFETIME;
	this->m_ticks = TargetAcquiredPermissionToFireEffect::LIFETIME;
	this->m_bs = new BoundingSphere(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), TargetAcquiredPermissionToFireEffect::RANGE);
	this->m_casterId = _casterId;
	this->m_messageQueue->pushOutgoingMessage(new CreateActionPositionMessage(Skill::TARGET_ACQUIRED_PERMISSION_TO_FIRE, _casterId, _position));

	//Turn off all towers
	vector<ServerEntity*> turrets = EntityHandler::getEntitiesByType(ServerEntity::TowerType);

	for(int i = 0; i < turrets.size(); i++)
	{
		((Turret*)turrets[i])->setActive(false);
	}

	this->m_damage = turrets.size() * TargetAcquiredPermissionToFireEffect::DAMAGE_PER_TOWER;
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

	if(this->m_ticks > this->m_lifetime)
	{
		vector<ServerEntity*> enemies = EntityHandler::getEntitiesByType(ServerEntity::EnemyType);
		ServerEntity *caster = EntityHandler::getServerEntity(this->m_casterId);

		for(int i = 0; i < enemies.size(); i++)
		{
			if(enemies[i]->intersects(*this->m_bs) == true)
			{
				((UnitEntity*)caster)->dealDamage(enemies[i], this->m_damage, this->m_damage);
			}
		}

		this->m_ticks--;
	}

	if(this->m_lifetime <= 0.0f)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}