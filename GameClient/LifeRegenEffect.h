#pragma once

#include "ServerEntity.h"

class LifeRegenEffect : public ServerEntity
{
private:
	unsigned int m_caster;
public:
	static const float HEAL_FACTOR;

	LifeRegenEffect(unsigned int _caster);
	~LifeRegenEffect();

	void update(float _dt);
};