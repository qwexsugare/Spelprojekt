#include "Tower.h"

Tower::Tower() : ServerEntity()
{
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 10.0f;
	this->m_type == ServerEntity::HeroType;
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

Tower::Tower(FLOAT3 position)
{
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 10.0f;
	this->m_type == ServerEntity::HeroType;
	this->m_positon = position;
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_positon.x, this->m_positon.y, this->m_positon.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

Tower::~Tower()
{

}

void Tower::update(float dt)
{
	if(this->m_attackCooldown <= 0.0f)
	{
		ServerEntity* se = EntityHandler::getClosestEnemy(this);

		if(se != NULL && (se->getPosition() - this->m_positon).length() <= this->m_attackRange)
		{
			EntityHandler::addEntity(new Projectile(this->m_positon, se->getPosition() - this->m_positon, 2.0f, 6.0f));
			this->m_attackCooldown = 2.0f;
		}
	}
	else
	{
		this->m_attackCooldown = this->m_attackCooldown - dt;
	}
}