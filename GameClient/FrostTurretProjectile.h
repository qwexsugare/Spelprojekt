#pragma once

#include "serverentity.h"

class FrostTurretProjectile : public ServerEntity
{
private:
	unsigned int m_master;
	unsigned int m_target;
	unsigned int m_masterOwner;
	float m_timeToImpact;

	float m_slowEffect;
	int m_damage;
public:
	static const int VELOCITY = 7.0f;

	FrostTurretProjectile(unsigned int _master, unsigned int _target, float _slowEffect, int _damage);
	~FrostTurretProjectile();

	void update(float _dt);
};

