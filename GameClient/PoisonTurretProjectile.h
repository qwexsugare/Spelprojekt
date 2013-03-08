#pragma once

#include "serverentity.h"

class PoisonTurretProjectile : public ServerEntity
{
private:
	unsigned int m_master;
	unsigned int m_target;
	unsigned int m_masterOwner;
	float m_timeToImpact;
	unsigned int m_mentalDamage;
public:
	static const float SLOW_EFFECT;
	static const int VELOCITY = 7.0f;

	PoisonTurretProjectile(unsigned int _master, unsigned int _target, unsigned int _mentalDamage);
	~PoisonTurretProjectile();

	void update(float _dt);
};

