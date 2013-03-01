#pragma once

#include "serverentity.h"

class FrostTurretProjectile : public ServerEntity
{
private:
	unsigned int m_master;
	unsigned int m_target;
	float m_timeToImpact;
public:
	static const float SLOW_EFFECT;
	static const int VELOCITY = 7.0f;

	FrostTurretProjectile(unsigned int _master, unsigned int _target);
	~FrostTurretProjectile();

	void update(float _dt);
};

