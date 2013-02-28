#include "PoisonTurretProjectile.h"
#include "EntityHandler.h"
#include "DelayedDamage.h"
#include "Graphics.h"
#include "MyAlgorithms.h"

const float PoisonTurretProjectile::SLOW_EFFECT = -1.5f;

PoisonTurretProjectile::PoisonTurretProjectile(unsigned int _master, unsigned int _target)
{
	m_master = _master;
	m_target = _target;
	m_visible = false;
	this->m_type = OtherType;
	ServerEntity* master = EntityHandler::getServerEntity(m_master);
	ServerEntity* target = EntityHandler::getServerEntity(m_target);
	float timeToImpact = (target->getPosition() - master->getPosition()).length()/PoisonTurretProjectile::VELOCITY;
	EntityHandler::addEntity(new DelayedDamage(m_master, m_target, timeToImpact, random(1,5), 0.0f, Skill::FROST_TURRET_PROJECTILE));
}

PoisonTurretProjectile::~PoisonTurretProjectile()
{

}

#include <fstream>
void PoisonTurretProjectile::update(float _dt)
{
	m_timeToImpact = max(m_timeToImpact-_dt, 0.0f);

	if(m_timeToImpact == 0.0f)
	{
		ServerEntity* target = EntityHandler::getServerEntity(m_target);
		if(target)
		{
			int damage = random(1, 25) * (((UnitEntity*)target)->getPoisonStacks()+1);
			int healthBefore = target->getHealth();
			target->takeDamage(this->getId(), 0, damage);
			((UnitEntity*)target)->addPoisonStack();

			// dbg
			ofstream file("output.txt", ios::app);
			if(file.is_open())
			{
				target = EntityHandler::getServerEntity(m_target);
				if(target)
					file << "Poison turret projectile did " << damage << " damage and reduced health from " << healthBefore << " to " << target->getHealth() << endl;
				else
					file << "Poison turret projectile did " << damage << " damage and reduced health from " << healthBefore << " to death" << endl;
				file.close();
			}

			// Remove me from server entity handler
			this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
		}
	}
}