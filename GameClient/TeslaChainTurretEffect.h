#pragma once

#include "serverentity.h"
#include "EntityHandler.h"

class TeslaChainTurretEffect : public ServerEntity
{
private:
	vector<unsigned int> m_invalidTargets;
	unsigned int m_firstTarget;
	float m_jumpTimer;
	int m_jumps;
	int m_maxJumps;
	int m_baseDamage;

	static const int MAX_JUMP_DISTANCE = 10;

public:
	TeslaChainTurretEffect(unsigned int _firstTarget, FLOAT3 _positon, int _maxJumps, int _baseDamage);
	~TeslaChainTurretEffect(void);

	void update(float _dt);
};