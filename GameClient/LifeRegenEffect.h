#pragma once

#include "ServerEntity.h"

class LifeRegenEffect : public ServerEntity
{
private:
	unsigned int m_caster;
	float m_tickTimer;
	float m_excessHeal;
public:
	static const float HEAL_FACTOR;

	LifeRegenEffect(unsigned int _caster);
	~LifeRegenEffect();

	void update(float _dt);
};