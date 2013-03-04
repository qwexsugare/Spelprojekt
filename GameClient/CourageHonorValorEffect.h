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
	static const float MOVEMENT_SPEED;
	static const float PHYSICAL_RESISTANCE;
	static const float MENTAL_DAMAGE;
	static const int AOE = 10;

	CourageHonorValorEffect(unsigned int _caster);
	~CourageHonorValorEffect();

	void update(float _dt);
};