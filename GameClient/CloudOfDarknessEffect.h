#pragma once

#include "ServerEntity.h"

class CloudOfDarknessEffect : public ServerEntity
{
private:
	vector<unsigned int> m_invalidTargets;
	unsigned int m_firstTarget;
	int m_sound;

	static const int MAX_JUMP_DISTANCE = 10;
public:
	CloudOfDarknessEffect(FLOAT3 _position);
	~CloudOfDarknessEffect();

	void update(float _dt);
};