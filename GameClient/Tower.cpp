#include "Tower.h"

Tower::Tower() : ServerEntity()
{
	this->m_attackCooldown = 0.0f;
	this->m_attackRange = 10.0f;
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