#pragma once

#include "ServerEntity.h"

class CloudOfDarknessEffect
 : public ServerEntity
{
private:
	float m_timer;
	float m_ticker;
	int m_damage;

	static const int AOE = 5;

	void tick();
public:
	static const int LIFETIME = 3;

	CloudOfDarknessEffect(FLOAT3 _position, int _damage, unsigned int _masterId);
	~CloudOfDarknessEffect();

	void update(float _dt);
};