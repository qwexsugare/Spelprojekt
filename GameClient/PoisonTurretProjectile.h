#pragma once

#include "serverentity.h"

class PoisonTurretProjectile : public ServerEntity
{
private:
	unsigned int m_master;
	unsigned int m_target;
	unsigned int m_masterOwner;
	float m_timeToImpact;
	int m_upgradeLevel;
public:
	static const float SLOW_EFFECT;
	static const int VELOCITY = 7.0f;

	PoisonTurretProjectile(unsigned int _master, unsigned int _target, int _upgradeLevel);
	~PoisonTurretProjectile();

	void update(float _dt);
};

