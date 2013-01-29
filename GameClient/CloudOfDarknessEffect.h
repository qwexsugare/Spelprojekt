#pragma once

#include "ServerEntity.h"
#include "EntityHandler.h"

class CloudOfDarknessEffect : public ServerEntity
{
private:
	float m_timer;
	int m_damage;

	static const int AOE = 10;
public:
	static const int LIFETIME = 3;

	CloudOfDarknessEffect(FLOAT3 _position, int _damage);
	~CloudOfDarknessEffect();

	void update(float _dt);
};