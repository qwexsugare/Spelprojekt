#include "Turret.h"
#include "EntityHandler.h"

Turret::Turret() : ServerEntity()
{
	this->m_attackCooldown = 0.0f;
	this->m_attackRangeProt = 10.0f;
	this->m_type = ServerEntity::TowerType;
}

Turret::Turret(FLOAT3 position)
{
	this->m_lifeTime = 1000.0f;
	this->m_attackCooldown = 0.0f;
	this->m_attackRangeProt = 10.0f;
	this->m_type = ServerEntity::TowerType;
	this->m_position = position;
}

Turret::Turret(FLOAT3 _position, float _attackCooldown, float _range, float _lifetime)
{
	m_range = BoundingSphere(XMFLOAT3(_position.x, _position.y, _position.z), _range);
	m_currentAttackCooldown = m_attackCooldown = _attackCooldown;
	m_lifeTime = _lifetime;
	m_position = _position;

	m_type = ServerEntity::TowerType;
}

Turret::~Turret()
{

}

void Turret::update(float _dt)
{
	m_currentAttackCooldown = max(m_currentAttackCooldown-_dt, 0.0f);

	if(m_currentAttackCooldown == 0.0f)
	{
		ServerEntity* entity = EntityHandler::getClosestEntityByType(this, ServerEntity::EnemyType);

		if(entity)
		{
			if(entity->intersects(m_range))
			{
				this->target(entity);
				this->m_currentAttackCooldown = m_attackCooldown;
			}
		}
	}
}