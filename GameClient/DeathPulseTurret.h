#pragma once

#include "turret.h"
#include "Datastructures.h"

class DeathPulseTurret : public Turret
{
private:

public:
	static const int COST = 120;
	static const float ATTACK_COOLDOWN;
	static const int RANGE = 10;

	DeathPulseTurret();
	DeathPulseTurret(FLOAT3 _pos, float _lifetime);
	~DeathPulseTurret();

	void target(ServerEntity* _target);
};

