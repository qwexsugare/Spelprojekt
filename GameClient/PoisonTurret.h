#pragma once

#include "turret.h"

class PoisonTurret : public Turret
{
public:
	static const int COST = 130;

	PoisonTurret();
	PoisonTurret(FLOAT3 _pos);
	~PoisonTurret();
};

