#include "Turret.h"
#include "EntityHandler.h"

Turret::Turret(FLOAT3 _position, float _attackCooldown, float _range, float _lifetime, unsigned int _ownerId, int _turretUpgrade) : ServerEntity()
{
	this->m_originalRange =_range; 
	this->m_range = BoundingSphere(XMFLOAT3(_position.x, _position.y, _position.z), _range);
	this->m_currentAttackCooldown = m_attackCooldown = _attackCooldown;
	this->m_lifeTime = _lifetime;
	this->m_position = _position;
	this->m_active = true;
	this->m_type = ServerEntity::TowerType;
	this->m_ownerId = _ownerId;
	m_turretUpgrade = _turretUpgrade;
	m_limiter = 0.0f;

	this->sendAttributesToClient();
}

Turret::~Turret()
{

}

const BoundingSphere& Turret::getRange()const
{
	return m_range;
}

int Turret::getTurretUpgrade()const
{
	return m_turretUpgrade;
}

void Turret::sendAttributesToClient()const
{
	m_messageQueue->pushOutgoingMessage(new AttributeUpdateMessage(m_id, 0,0,0,0,0,m_lifeTime,0,0,0,0));
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

		if(m_limiter <= 0.0f)
		{
			this->m_messageQueue->pushOutgoingMessage(new updateEntityHealth(m_id, m_lifeTime));
			m_limiter = 1.0f;
		}
		m_limiter-=_dt;
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