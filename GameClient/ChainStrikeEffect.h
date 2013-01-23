#pragma once

#include "ServerEntity.h"
#include "Model.h"

class ChainStrikeEffect : public ServerEntity
{
private:
	vector<unsigned int> m_invalidTargets;
	unsigned int m_firstTarget;
	float m_jumpTimer;
	int m_jumps;
	int m_maxJumps;
	int m_sound;

	static const int MAX_JUMP_DISTANCE = 10;
public:
	ChainStrikeEffect(unsigned int _firstTarget, FLOAT3 _positon, int _maxJumps);
	~ChainStrikeEffect();

	void update(float _dt);
};