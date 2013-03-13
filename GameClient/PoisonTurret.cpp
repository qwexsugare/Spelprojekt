#include "PoisonTurret.h"
#include "Graphics.h"
#include "MyAlgorithms.h"
#include "PoisonTurretProjectile.h"
#include "EntityHandler.h"

const float PoisonTurret::ATTACK_COOLDOWN = 1.5f;

PoisonTurret::PoisonTurret(FLOAT3 _pos, UnitEntity *_creator) :
	Turret(_pos, ATTACK_COOLDOWN, RANGE, _creator->getTurretDuration() * 20, _creator->getId(), _creator->getTurretConstruction())
{
	this->m_modelId = 2;
	this->m_mentalDamage = _creator->getTurretConstruction() / 4 + 1;
	
	Model* temp = g_graphicsEngine->createModel("PoisonTurret", _pos);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
}

PoisonTurret::~PoisonTurret()
{

}

void PoisonTurret::target(ServerEntity* _target)
{
	EntityHandler::addEntity(new PoisonTurretProjectile(this->getId(), _target->getId(), this->m_mentalDamage));
}

int PoisonTurret::getCost()
{
	return PoisonTurret::COST;
}