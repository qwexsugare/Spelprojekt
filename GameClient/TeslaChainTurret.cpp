#include "TeslaChainTurret.h"
#include "Graphics.h"
#include "EntityHandler.h"

const float TeslaChainTurret::RANGE = 2.0f;
const float TeslaChainTurret::COOLDOWN = 2.0f;

TeslaChainTurret::TeslaChainTurret(FLOAT3 _position, UnitEntity *_creator) : Turret(_position, TeslaChainTurret::COOLDOWN, TeslaChainTurret::RANGE, 20 * _creator->getTurretDuration())
{
	this->m_damage = 20;
	this->m_numberOfHits = 1 + _creator->getTurretConstruction() / 4;
	this->m_modelId = 3;
	
	Model* temp = g_graphicsEngine->createModel("LightningTurret", _position);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
}

TeslaChainTurret::~TeslaChainTurret()
{

}

void TeslaChainTurret::update(float dt)
{
	this->m_lifeTime = this->m_lifeTime - dt;

	if(this->m_attackCooldown <= 0.0f)
	{
		ServerEntity* se = EntityHandler::getClosestEntityByType(this, EnemyType);

		if(se != NULL && (se->getPosition() - this->m_position).length() <= this->m_attackRangeProt)
		{
			EntityHandler::addEntity(new ChainStrikeEffect(se->getId(), this->m_position, this->m_numberOfHits, this->m_damage, this->m_id));
			this->m_attackCooldown = TeslaChainTurret::COOLDOWN;
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

void TeslaChainTurret::target(ServerEntity* _target)
{
	int dbg = 1;
}

int TeslaChainTurret::getCost()
{
	return TeslaChainTurret::COST;
}