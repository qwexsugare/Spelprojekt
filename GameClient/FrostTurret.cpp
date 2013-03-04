#include "FrostTurret.h"
#include "Graphics.h"
#include "FrostTurretProjectile.h"
#include "EntityHandler.h"

const float FrostTurret::ATTACK_COOLDOWN = 1.0f;

FrostTurret::FrostTurret()
{

}

FrostTurret::FrostTurret(FLOAT3 _pos, UnitEntity *_creator) : Turret(_pos, ATTACK_COOLDOWN, RANGE, _creator->getTurretDuration() * 20)
{
	this->m_modelId = 5;
	this->m_slowEffect = (1 + _creator->getTurretConstruction() / 4) * -0.1;
	
	Model* temp = g_graphicsEngine->createModel("FrostTurret", _pos);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
}

FrostTurret::~FrostTurret()
{

}

void FrostTurret::target(ServerEntity* _target)
{	
	EntityHandler::addEntity(new FrostTurretProjectile(this->getId(), _target->getId(), this->m_slowEffect));
}

int FrostTurret::getCost()
{
	return FrostTurret::COST;
}