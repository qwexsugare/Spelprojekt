#include "DeathPulseTurret.h"
#include "Graphics.h"
#include "MyAlgorithms.h"
#include "EntityHandler.h"
#include "DelayedDamage.h"

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
	this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::DEATH_PULSE_TURRET_PROJECTILE, this->getId(), _target->getId(), FLOAT3()));

	unsigned int targetId = _target->getId();

	int damage = random(1, 10);
	int healthBefore = _target->getHealth();
	_target->takeDamage(this->getId(), 0, damage);

	// dbg
	ofstream file("output.txt", ios::app);
	if(file.is_open())
	{
		_target = EntityHandler::getServerEntity(targetId);
		if(_target)
			file << "Death Pulse turret projectile did " << damage << " damage and reduced health from " << healthBefore << " to " << _target->getHealth() << endl;
		else
			file << "Death Pulse turret projectile did " << damage << " damage and reduced health from " << healthBefore << " to death" << endl;
		file.close();
	}
}