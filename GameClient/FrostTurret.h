#pragma once

#include "turret.h"

class FrostTurret : public Turret
{
public:
	static const int COST = 100;
	static const float ATTACK_COOLDOWN;
	static const int RANGE = 3;
	static const float SLOW_EFFECT;

	FrostTurret();
	FrostTurret(FLOAT3 _pos, float _lifetime);
	~FrostTurret();

	void target(ServerEntity* _target);
};

