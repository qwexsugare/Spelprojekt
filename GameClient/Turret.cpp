#include "Turret.h"

Turret::Turret() : ServerEntity()
{
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 10.0f;
	this->m_type = ServerEntity::TowerType;
}

Turret::Turret(FLOAT3 position)
{
	this->m_lifeTime = 1000.0f;
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 10.0f;
	this->m_type = ServerEntity::TowerType;
	this->m_position = position;
}

Turret::~Turret()
{

}