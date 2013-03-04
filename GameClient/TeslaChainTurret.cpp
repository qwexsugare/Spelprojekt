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

void TeslaChainTurret::target(ServerEntity* _target)
{
	EntityHandler::addEntity(new ChainStrikeEffect(_target->getId(), this->m_numberOfHits, this->m_damage, this->m_id));
	this->m_attackCooldown = TeslaChainTurret::COOLDOWN;
}