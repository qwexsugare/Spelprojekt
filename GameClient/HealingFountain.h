#pragma once
#include "ServerEntity.h"
#include "EntityHandler.h"

class HealingFountain : public ServerEntity
{
private:
	static const float RANGE;

	float m_timeSinceLastTick;
public:
	HealingFountain(FLOAT3 _pos);
	~HealingFountain();

	void update(float _dt);
};

