#pragma once

#include "ServerEntity.h"
#include "Skill.h"

class CourageHonorValorEffect : public ServerEntity
{
private:
	static vector<unsigned int> m_affectedGuys;
	float m_timer;
	unsigned int m_caster;
public:
	static const float MOVEMENT_SPEED_BASE;
	static const float MOVEMENT_SPEED_FACTOR;
	static const float MENTAL_RESISTANCE_FACTOR;
	static const float MENTAL_RESISTANCE_BASE;
	static const float MENTAL_DAMAGE_FACTOR;
	static const float MENTAL_DAMAGE_BASE;
	static const int AOE = 10;

	CourageHonorValorEffect(unsigned int _caster);
	~CourageHonorValorEffect();

	void update(float _dt);
};