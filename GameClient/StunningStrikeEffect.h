#pragma once

#include "ServerEntity.h"

class StunningStrikeEffect : public ServerEntity
{
private:
	float m_timer;
public:
	static const int LIFETIME = 3;
	static const int AOE = 10;

	StunningStrikeEffect(FLOAT3 _position);
	~StunningStrikeEffect();

	void update(float _dt);
};