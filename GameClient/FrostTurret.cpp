#include "FrostTurret.h"
#include "Graphics.h"
#include "FrostTurretProjectile.h"
#include "EntityHandler.h"
#include "MyAlgorithms.h"

const float FrostTurret::ATTACK_COOLDOWN = 1.5f;

FrostTurret::FrostTurret(FLOAT3 _pos, UnitEntity *_creator) :
	Turret(_pos, ATTACK_COOLDOWN, RANGE, _creator->getTurretDuration() * 20, _creator->getId(), _creator->getTurretConstruction())
{
	this->m_modelId = 5;
	this->m_slowEffect = (1 + _creator->getTurretConstruction() / 4) * -0.1;
	
	Model* temp = g_graphicsEngine->createModel("FrostGun", _pos);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);

	this->m_minDamage = (_creator->getTurretDamageUpgrade() * _creator->getTurretConstruction()) / 4 + 5;
	this->m_maxDamage = (_creator->getTurretDamageUpgrade() * _creator->getTurretConstruction()) / 2 + 10;
	m_updateRotLimiter = 0.0f;
}

FrostTurret::~FrostTurret()
{

}

void FrostTurret::target(ServerEntity* _target)
{
	EntityHandler::addEntity(new FrostTurretProjectile(this->getId(), _target->getId(), this->m_slowEffect, random(this->m_minDamage, this->m_maxDamage)));
}

void FrostTurret::updateSpecificTurret(float _dt)
{
	ServerEntity* entity = EntityHandler::getClosestEntityByType(this, ServerEntity::EnemyType);

	if(entity)
	{
		if(entity->intersects(this->getRange()))
		{
			FLOAT3 distance = entity->getPosition() - this->m_position;
			float desiredRotation = atan2(-distance.x, -distance.z) + D3DX_PI/2.0f;

			if(desiredRotation > m_rotation.x)
				m_rotation.x = min(m_rotation.x+_dt, desiredRotation);
			else
				m_rotation.x = max(m_rotation.x-_dt, desiredRotation);

			m_updateRotLimiter = max(m_updateRotLimiter-_dt, 0.0f);
			if(m_updateRotLimiter == 0.0f)
			{
				this->m_messageQueue->pushOutgoingMessage(new UpdateEntityMessage(
					this->m_id, this->m_position.x, this->m_position.z, this->m_rotation.x, this->m_position.x, this->m_position.z, this->m_position.x, this->m_position.z, 0.0f));
				m_updateRotLimiter = 0.1f;
			}
		}
	}
}

int FrostTurret::getCost()
{
	return FrostTurret::COST;
}
