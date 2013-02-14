#include "TeslaChainTurret.h"

TeslaChainTurret::TeslaChainTurret(FLOAT3 _position, int turretLifeUpgrade, int turretUpgrade)
{
	this->m_lifeTime = 20 * turretLifeUpgrade;
	this->m_damage = 20;
	this->m_cooldown = 2.0f;
	this->m_attackRange = 2.0f;
	this->m_attackCooldown = this->m_cooldown;
	this->m_numberOfHits = 2 + turretUpgrade / 4;
}

TeslaChainTurret::~TeslaChainTurret()
{

}

void TeslaChainTurret::update(float dt)
{
	this->m_lifeTime = this->m_lifeTime - dt;

	if(this->m_attackCooldown <= 0.0f)
	{
		ServerEntity* se = EntityHandler::getClosestEnemy(this);

		if(se != NULL && (se->getPosition() - this->m_position).length() <= this->m_attackRange)
		{
			EntityHandler::addEntity(new ChainStrikeEffect(se->getId(), this->m_position, this->m_numberOfHits, this->m_damage));
			this->m_attackCooldown = this->m_cooldown;
		}
	}
	else
	{
		this->m_attackCooldown = this->m_attackCooldown - dt;
	}

	if(this->m_lifeTime <= 0.0f)
	{
		this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
	}
}