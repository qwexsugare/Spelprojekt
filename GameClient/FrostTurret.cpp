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
	FLOAT3 distance = _target->getPosition() - this->m_position;
	this->m_rotation.x = atan2(-distance.x, -distance.z);
	m_rotation.x += D3DX_PI/2.0f;
	this->m_messageQueue->pushOutgoingMessage(new UpdateEntityMessage(this->m_id, this->m_position.x, this->m_position.z, this->m_rotation.x, this->m_position.x, this->m_position.z, this->m_position.x, this->m_position.z, 0.0f));
	EntityHandler::addEntity(new FrostTurretProjectile(this->getId(), _target->getId(), this->m_slowEffect));
}