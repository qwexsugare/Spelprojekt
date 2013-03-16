#include "TeslaChainTurret.h"
#include "Graphics.h"
#include "EntityHandler.h"
#include "MyAlgorithms.h"

const float TeslaChainTurret::RANGE = 2.0f;
const float TeslaChainTurret::COOLDOWN = 2.0f;

TeslaChainTurret::TeslaChainTurret(FLOAT3 _position, UnitEntity *_creator) :
	Turret(_position, TeslaChainTurret::COOLDOWN, TeslaChainTurret::RANGE, 20 * _creator->getTurretDuration(), _creator->getId(), _creator->getTurretConstruction())
{
	this->m_minDamage = (_creator->getTurretDamageUpgrade() * _creator->getTurretConstruction()) / 4;
	this->m_maxDamage = (_creator->getTurretDamageUpgrade() * _creator->getTurretConstruction()) / 2;
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
	EntityHandler::addEntity(new ChainStrikeEffect(_target->getId(), this->m_numberOfHits, random(this->m_minDamage, this->m_maxDamage), this->m_id));
	this->m_attackCooldown = TeslaChainTurret::COOLDOWN;
}

int TeslaChainTurret::getCost()
{
	return TeslaChainTurret::COST;
}