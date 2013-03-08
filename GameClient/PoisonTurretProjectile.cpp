#include "PoisonTurretProjectile.h"
#include "EntityHandler.h"
#include "DelayedDamage.h"
#include "Graphics.h"
#include "MyAlgorithms.h"
#include "Turret.h"

const float PoisonTurretProjectile::SLOW_EFFECT = -1.5f;

PoisonTurretProjectile::PoisonTurretProjectile(unsigned int _master, unsigned int _target, unsigned int _mentalDamage)
{
	m_master = _master;
	m_target = _target;
	m_visible = false;
	this->m_type = OtherType;
	ServerEntity* master = EntityHandler::getServerEntity(m_master);
	ServerEntity* target = EntityHandler::getServerEntity(m_target);
	m_timeToImpact = (target->getPosition() - master->getPosition()).length()/PoisonTurretProjectile::VELOCITY;
	this->m_masterOwner = ((Turret*)master)->getOwnerId();
	this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::POISON_TURRET_PROJECTILE, m_master, m_target, master->getPosition()));
	this->m_mentalDamage = _mentalDamage;
}

PoisonTurretProjectile::~PoisonTurretProjectile()
{

}

#include <sstream>
void PoisonTurretProjectile::update(float _dt)
{
	m_timeToImpact = max(m_timeToImpact-_dt, 0.0f);

	if(m_timeToImpact == 0.0f)
	{
		ServerEntity* target = EntityHandler::getServerEntity(m_target);
		if(target)
		{
			int damage = random(1, 25) + (((UnitEntity*)target)->getPoisonStacks()+1) * this->m_mentalDamage;
			int healthBefore = target->getHealth();
			target->takeDamage(this->m_masterOwner, 0, damage);
			((UnitEntity*)target)->addPoisonStack();

			// dbg
			stringstream ss;
			target = EntityHandler::getServerEntity(m_target);
			if(target)
				ss << "Poison turret projectile did " << damage << " damage and reduced health from " << healthBefore << " to " << target->getHealth() << endl;
			else
				ss << "Poison turret projectile did " << damage << " damage and reduced health from " << healthBefore << " to death" << endl;
			OutputDebugString(ss.str().c_str());

			// Remove me from server entity handler
			this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
		}
	}
}