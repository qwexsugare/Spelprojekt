#pragma once

#include "Turret.h"
#include "ChainStrikeEffect.h"
#include "DataStructures.h"
#include "UnitEntity.h"

class TeslaChainTurret : public Turret
{
private:
	int m_damage;
	int m_numberOfHits;
public:
	static const int COST = 150;
	static const float RANGE;
	static const float COOLDOWN;

	TeslaChainTurret(FLOAT3 _position, UnitEntity *_creator);
	~TeslaChainTurret();

	void update(float dt);
	void target(ServerEntity* _target);
};

