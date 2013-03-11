#pragma once

#include "ServerEntity.h"

class ChainStrikeEffect : public ServerEntity
{
private:
	vector<unsigned int> m_invalidTargets;
	unsigned int m_firstTarget;
	float m_jumpTimer;
	int m_jumps;
	int m_maxJumps;
	int m_baseDamage;
	unsigned int m_masterId;
	unsigned int m_lastTargetId;

	static const int MAX_JUMP_DISTANCE = 5;
public:
	static const FLOAT TIME_BETWEEN_JUMPS;

	ChainStrikeEffect(unsigned int _firstTarget, int _maxJumps, int _baseDamage, unsigned int _masterId);
	~ChainStrikeEffect();

	void update(float _dt);
};