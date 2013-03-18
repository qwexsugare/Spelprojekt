#pragma once

#include "ServerEntity.h"

class HypnoticStareEffect : public ServerEntity
{
private:
	unsigned int m_affectedUnit;
	float m_timer;
	int m_mentalDamage;
	float m_movementSpeed;
public:
	HypnoticStareEffect(unsigned int _affectedUnit, unsigned int _casterId, int _wits);
	~HypnoticStareEffect();

	void update(float _dt);
};