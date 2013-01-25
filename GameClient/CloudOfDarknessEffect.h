#pragma once

#include "ServerEntity.h"

class CloudOfDarknessEffect : public ServerEntity
{
private:
	vector<unsigned int> m_invalidTargets;
	unsigned int m_firstTarget;
	int m_sound;
	float m_timer;
	int m_damage;
	
	static const int LIFETIME = 3;
	static const int AOE = 200;
public:
	CloudOfDarknessEffect(FLOAT3 _position, int _damage);
	~CloudOfDarknessEffect();

	void update(float _dt);
};