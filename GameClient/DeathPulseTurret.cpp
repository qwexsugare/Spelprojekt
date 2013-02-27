#include "DeathPulseTurret.h"
#include "Graphics.h"
#include "MyAlgorithms.h"

const float DeathPulseTurret::ATTACK_COOLDOWN = 1.0f;

DeathPulseTurret::DeathPulseTurret()
{

}

DeathPulseTurret::DeathPulseTurret(FLOAT3 _pos, float _lifetime) : Turret(_pos, ATTACK_COOLDOWN, RANGE, _lifetime)
{
	this->m_modelId = 4;
	
	Model* temp = g_graphicsEngine->createModel("DeathTurret", _pos);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
}

DeathPulseTurret::~DeathPulseTurret()
{

}

void DeathPulseTurret::target(ServerEntity* _target)
{
	this->dealDamage(_target, random(1, 10), 0);
	//this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::DEMONIC_PRESENCE, 0, _target->getId(), _target->getPosition()));
}