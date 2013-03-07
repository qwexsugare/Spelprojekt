#include "DeathPulseTurret.h"
#include "Graphics.h"
#include "MyAlgorithms.h"
#include "EntityHandler.h"
#include "DelayedDamage.h"

const float DeathPulseTurret::ATTACK_COOLDOWN = 1.0f;

DeathPulseTurret::DeathPulseTurret()
{

}

DeathPulseTurret::DeathPulseTurret(FLOAT3 _pos, UnitEntity *_creator) : Turret(_pos, ATTACK_COOLDOWN, RANGE, _creator->getTurretDuration() * 20, _creator->getId())
{
	this->m_modelId = 4;
	
	Model* temp = g_graphicsEngine->createModel("DeathTurret", _pos);
	m_obb = new BoundingOrientedBox(*temp->getObb());
	g_graphicsEngine->removeModel(temp);
}

DeathPulseTurret::~DeathPulseTurret()
{

}

#include <sstream>
void DeathPulseTurret::target(ServerEntity* _target)
{
	this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::DEATH_PULSE_TURRET_PROJECTILE, this->getId(), _target->getId(), FLOAT3()));

	unsigned int targetId = _target->getId();

	int damage = random(1, 10);
	int healthBefore = _target->getHealth();
	_target->takeDamage(this->m_ownerId, 0, damage);

	// dbg
	stringstream ss;
	ServerEntity* target = EntityHandler::getServerEntity(targetId);
	if(target)
		ss << "Death Pulse turret projectile did " << damage << " damage and reduced health from " << healthBefore << " to " << target->getHealth() << endl;
	else
		ss << "Death Pulse turret projectile did " << damage << " damage and reduced health from " << healthBefore << " to death" << endl;
	OutputDebugString(ss.str().c_str());
}

int DeathPulseTurret::getCost()
{
	return DeathPulseTurret::COST;
}