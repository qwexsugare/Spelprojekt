#pragma once

#include "ServerEntity.h"

class HypnoticStareEffect : public ServerEntity
{
private:
	unsigned int m_affectedUnit;
	float m_timer;
public:
	HypnoticStareEffect(unsigned int _affectedUnit, unsigned int _casterId, float _duration);
	~HypnoticStareEffect();

	void update(float _dt);
};