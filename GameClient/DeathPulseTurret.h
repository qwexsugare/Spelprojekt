#pragma once

#include "turret.h"
#include "Datastructures.h"
#include "UnitEntity.h"

class DeathPulseTurret : public Turret
{
private:
	int m_turretUpgrade;
public:
	static const int COST = 120;
	static const float ATTACK_COOLDOWN;
	static const int RANGE = 10;

	DeathPulseTurret();
	DeathPulseTurret(FLOAT3 _pos, UnitEntity *_creator);
	~DeathPulseTurret();

	void target(ServerEntity* _target);
	int getCost();
};

