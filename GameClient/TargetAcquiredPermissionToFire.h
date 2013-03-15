#pragma once

#include "skill.h"
#include "TargetAcquiredPermissionToFireEffect.h"

class TargetAcquiredPermissionToFire : public Skill
{
private:
	static const float COOLDOWN;
public:
	static const float RANGE;

	TargetAcquiredPermissionToFire();
	~TargetAcquiredPermissionToFire();

	virtual bool activate(FLOAT3 _position, unsigned int _senderId);
	void updateSpecificSkill(float _dt);
};

