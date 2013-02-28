#pragma once

#include "turret.h"

class PoisonTurret : public Turret
{
public:
	static const int COST = 130;
	static const float ATTACK_COOLDOWN;
	static const int RANGE = 5;

	PoisonTurret();
	PoisonTurret(FLOAT3 _pos, float _lifetime);
	~PoisonTurret();

	void target(ServerEntity* _target);
};

