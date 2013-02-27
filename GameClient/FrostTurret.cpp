#include "FrostTurret.h"
#include "Graphics.h"
#include "MyAlgorithms.h"
#include "FrostTurretEffect.h"

const float FrostTurret::ATTACK_COOLDOWN = 1.0f;
const float FrostTurret::SLOW_EFFECT = -1.5f;

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
	this->dealDamage(_target, random(1, 5), 0);
	((UnitEntity*)_target)->applyFrostTurretSlowEffect(SLOW_EFFECT);
	
	//EntityHandler::addEntity(new FrostTurretEffect(_target->getId()));
	//this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::DEMONIC_PRESENCE, 0, _target->getId(), _target->getPosition()));
}