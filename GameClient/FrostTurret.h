#pragma once

#include "turret.h"

class FrostTurret : public Turret
{
public:
	static const int COST = 100;

	FrostTurret();
	FrostTurret(FLOAT3 _pos);
	~FrostTurret();
};

