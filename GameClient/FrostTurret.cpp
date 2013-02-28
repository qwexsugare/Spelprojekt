#include "FrostTurret.h"
#include "Graphics.h"
#include "FrostTurretProjectile.h"
#include "EntityHandler.h"

const float FrostTurret::ATTACK_COOLDOWN = 1.0f;

FrostTurret::FrostTurret()
{

}

FrostTurret::FrostTurret(FLOAT3 _pos, float _lifetime) : Turret(_pos, ATTACK_COOLDOWN, RANGE, _lifetime)
{
	this->m_modelId = 5;
	
	Model* temp = g_graphicsEngine->createModel("FrostTurret", _pos);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
}

FrostTurret::~FrostTurret()
{

}

void FrostTurret::target(ServerEntity* _target)
{	
	EntityHandler::addEntity(new FrostTurretProjectile(this->getId(), _target->getId()));
}