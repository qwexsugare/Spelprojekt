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
	this->m_originalRange =_range; 
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
	this->m_lifeTime = this->m_lifeTime - _dt;
	m_currentAttackCooldown = max(m_currentAttackCooldown-_dt, 0.0f);

	if(m_currentAttackCooldown == 0.0f)
	{
		ServerEntity* entity = EntityHandler::getClosestEntityByType(this, ServerEntity::EnemyType);

		if(entity)
		{
			if(entity->intersects(m_range))
			{
				this->target(entity);
				this->m_currentAttackCooldown = m_attackCooldown - this->m_readyAimFire;
			}
		}
	}

	if(this->m_lifeTime <= 0.0f)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}

void Turret::addLifetime(float _dt)
{
	this->m_lifeTime = this->m_lifeTime + _dt;
}

void Turret::setReadyAimFire(float _readyAimFire)
{
	this->m_readyAimFire = _readyAimFire;
	this->m_range.Radius = this->m_originalRange + this->m_readyAimFire;
}