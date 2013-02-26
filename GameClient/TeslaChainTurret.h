#pragma once

#include "Turret.h"
#include "ChainStrikeEffect.h"
#include "DataStructures.h"

class TeslaChainTurret : public Turret
{
private:
	float m_cooldown;
	int m_damage;
	int m_numberOfHits;
public:
	TeslaChainTurret(FLOAT3 _position, int turretLifeUpgrade, int turretUpgrade);
	~TeslaChainTurret();

	void update(float dt);
};

