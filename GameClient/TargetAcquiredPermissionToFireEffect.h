#pragma once

#include "serverentity.h"
#include "EntityHandler.h"
#include "Turret.h"

class TargetAcquiredPermissionToFireEffect : public ServerEntity
{
private:
	FLOAT3 m_position;
	float m_lifetime;
	int m_ticks;
	int m_damage;
	unsigned int m_casterId;
public:
	static const float LIFETIME;
	static const float RANGE;
	static const int DAMAGE_PER_TOWER = 10;

	TargetAcquiredPermissionToFireEffect(unsigned int _casterId, FLOAT3 _position);
	~TargetAcquiredPermissionToFireEffect();

	void update(float _dt);
};

