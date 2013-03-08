#include "Turret.h"
#include "EntityHandler.h"

Turret::Turret() : ServerEntity()
{
	this->m_attackCooldown = 0.0f;
	this->m_attackRangeProt = 10.0f;
	this->m_type = ServerEntity::TowerType;
	this->m_active = true;
}

Turret::Turret(FLOAT3 position)
{
	this->m_lifeTime = 1000.0f;
	this->m_attackCooldown = 0.0f;
	this->m_attackRangeProt = 10.0f;
	this->m_type = ServerEntity::TowerType;
	this->m_position = position;
	this->m_active = true;
}

Turret::Turret(FLOAT3 _position, float _attackCooldown, float _range, float _lifetime, unsigned int _ownerId)
{
	this->m_originalRange =_range; 
	this->m_range = BoundingSphere(XMFLOAT3(_position.x, _position.y, _position.z), _range);
	this->m_currentAttackCooldown = m_attackCooldown = _attackCooldown;
	this->m_lifeTime = _lifetime;
	this->m_position = _position;
	this->m_active = true;
	this->m_type = ServerEntity::TowerType;
	this->m_ownerId = _ownerId;
}

Turret::~Turret()
{

}

const BoundingSphere& Turret::getRange()const
{
	return m_range;
}

void Turret::update(float _dt)
{
	this->m_lifeTime = max(this->m_lifeTime - _dt, 0.0f);

	if(this->m_lifeTime == 0.0f)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
	else
	{
		m_currentAttackCooldown = max(m_currentAttackCooldown-_dt, 0.0f);

		if(this->m_active == true)
		{
			this->updateSpecificTurret(_dt);

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
	}
}

void Turret::updateSpecificTurret(float _dt)
{

}

void Turret::addLifetime(float _dt)
{
	this->m_lifeTime = this->m_lifeTime + _dt;
}

void Turret::setReadyAimFire(float _readyAimFire)
{
	this->m_range.Radius = this->m_originalRange + _readyAimFire;
	this->m_currentAttackCooldown = min(this->m_currentAttackCooldown, this->m_attackCooldown - _readyAimFire);
}

void Turret::setActive(bool _active)
{
	this->m_active = _active;
}

unsigned int Turret::getOwnerId()
{
	return this->m_ownerId;
}