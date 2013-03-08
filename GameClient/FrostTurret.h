#pragma once

#include "turret.h"
#include "UnitEntity.h"

class FrostTurret : public Turret
{
private:
	float m_slowEffect;
	ServerEntity* m_base;
public:
	static const int COST = 100;
	static const float ATTACK_COOLDOWN;
	static const int RANGE = 5;

	FrostTurret();
	FrostTurret(FLOAT3 _pos, UnitEntity *_creator);
	~FrostTurret();

	void target(ServerEntity* _target);
	void updateSpecificTurret(float _dt);
	int getCost();
};

