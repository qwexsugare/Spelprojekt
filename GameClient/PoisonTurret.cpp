#include "PoisonTurret.h"
#include "Graphics.h"
#include "MyAlgorithms.h"
#include "PoisonTurretProjectile.h"
#include "EntityHandler.h"

const float PoisonTurret::ATTACK_COOLDOWN = 1.0f;

PoisonTurret::PoisonTurret()
{

}

PoisonTurret::PoisonTurret(FLOAT3 _pos, float _lifetime) : Turret(_pos, ATTACK_COOLDOWN, RANGE, _lifetime)
{
	this->m_modelId = 2;
	
	Model* temp = g_graphicsEngine->createModel("PoisonTurret", _pos);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
}

PoisonTurret::~PoisonTurret()
{

}

void PoisonTurret::target(ServerEntity* _target)
{
	EntityHandler::addEntity(new PoisonTurretProjectile(this->getId(), _target->getId()));
}