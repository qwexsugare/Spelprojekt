#pragma once

#include "turret.h"
#include "Datastructures.h"

class DeathPulseTurret : public Turret
{
private:

public:
	static const int COST = 120;

	DeathPulseTurret();
	DeathPulseTurret(FLOAT3 _pos);
	~DeathPulseTurret();
};

