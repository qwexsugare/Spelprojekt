#pragma once

#include "serverentity.h"
#include "EntityHandler.h"
#include "Turret.h"

class TargetAcquiredPermissionToFireEffect : public ServerEntity
{
private:
	FLOAT3 m_position;
	float m_lifetime;
public:
	TargetAcquiredPermissionToFireEffect(FLOAT3 _position);
	~TargetAcquiredPermissionToFireEffect();

	void update(float _dt);
};

