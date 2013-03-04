#pragma once

#include "turret.h"
#include "UnitEntity.h"

class PoisonTurret : public Turret
{
private:
	unsigned int m_mentalDamage;
public:
	static const int COST = 130;
	static const float ATTACK_COOLDOWN;
	static const int RANGE = 5;

	PoisonTurret();
	PoisonTurret(FLOAT3 _pos, UnitEntity *_creator);
	~PoisonTurret();

	void target(ServerEntity* _target);
};

