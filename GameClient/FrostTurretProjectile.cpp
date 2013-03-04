#include "FrostTurretProjectile.h"
#include "EntityHandler.h"
#include "DelayedDamage.h"
#include "MyAlgorithms.h"

FrostTurretProjectile::FrostTurretProjectile(unsigned int _master, unsigned int _target, float _slowEffect)
{
	m_master = _master;
	m_target = _target;
	m_visible = false;
	this->m_type = OtherType;
	this->m_slowEffect = _slowEffect;
	ServerEntity* master = EntityHandler::getServerEntity(m_master);
	ServerEntity* target = EntityHandler::getServerEntity(m_target);
	m_timeToImpact = (target->getPosition() - master->getPosition()).length()/FrostTurretProjectile::VELOCITY;

	// Calc position of projectile with offset from the pipe of the turret and send network msg
	FLOAT3 distance = target->getPosition() - master->getPosition();
	distance = distance/distance.length();
	this->m_messageQueue->pushOutgoingMessage(new CreateActionTargetMessage(Skill::FROST_TURRET_PROJECTILE, m_master, m_target, master->getPosition()+distance*0.5f));
}

FrostTurretProjectile::~FrostTurretProjectile()
{

}

void FrostTurretProjectile::update(float _dt)
{
	m_timeToImpact = max(m_timeToImpact-_dt, 0.0f);

	if(m_timeToImpact == 0.0f)
	{
		ServerEntity* target = EntityHandler::getServerEntity(m_target);
		if(target)
		{
			int damage = random(1, 5);
			int healthBefore = target->getHealth();
			target->takeDamage(m_master, damage, 0);
			((UnitEntity*)target)->applyFrostTurretSlowEffect(this->m_slowEffect);

			// dbg
			ofstream file("output.txt", ios::app);
			if(file.is_open())
			{
				target = EntityHandler::getServerEntity(m_target);
				if(target)
					file << "Frost turret projectile did " << damage << " damage and reduced health from " << healthBefore << " to " << target->getHealth() << endl;
				else
					file << "Frost turret projectile did " << damage << " damage and reduced health from " << healthBefore << " to death" << endl;
				file.close();
			}

			// Remove me from server entity handler
			this->m_messageQueue->pushOutgoingMessage(new RemoveServerEntityMessage(0, EntityHandler::getId(), this->m_id));
		}
	}
}