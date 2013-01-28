#include "Tower.h"

Tower::Tower() : ServerEntity()
{
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 10.0f;
	this->m_type = ServerEntity::OtherType;
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

Tower::Tower(FLOAT3 position)
{
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 10.0f;
	this->m_type = ServerEntity::OtherType;
	this->m_position = position;
	this->m_obb = new BoundingOrientedBox(XMFLOAT3(this->m_position.x, this->m_position.y, this->m_position.z), XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	this->setModelId(2);
}

Tower::~Tower()
{

}

void Tower::update(float dt)
{
	if(this->m_attackCooldown <= 0.0f)
	{
		ServerEntity* se = EntityHandler::getClosestEnemy(this);

		if(se != NULL && (se->getPosition() - this->m_position).length() <= this->m_attackRange)
		{
			EntityHandler::addEntity(new Projectile(this->m_position, se->getPosition() - this->m_position, 2.0f, 6.0f, (UnitEntity*)this));
			this->m_attackCooldown = 2.0f;
		}
	}
	else
	{
		this->m_attackCooldown = this->m_attackCooldown - dt;
	}
}