#pragma once

#include "ServerEntity.h"

class StunningStrikeEffect : public ServerEntity
{
private:
	float m_timer;
	int m_damage;
	
	static const int LIFETIME = 3;
	static const int AOE = 200;
public:
	StunningStrikeEffect(FLOAT3 _position, int _damage);
	~StunningStrikeEffect();

	void update(float _dt);
};