#pragma once

#include "ServerEntity.h"

class CloudOfDarknessEffect : public ServerEntity
{
private:
	int m_sound;
	float m_timer;
	int m_damage;
	
	static const int LIFETIME = 3;
	static const int AOE = 10;
public:
	CloudOfDarknessEffect(FLOAT3 _position, int _damage);
	~CloudOfDarknessEffect();

	void update(float _dt);
};