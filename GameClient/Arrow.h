#pragma once

#include "unitentity.h"

class Arrow : public UnitEntity
{
private:
	unsigned int m_target;
	unsigned int m_caster;
	float m_timeToImpact;
public:
	static const int VELOCITY = 10.0f;

	Arrow();
	Arrow(float _distance, unsigned int _target, unsigned int _caster);
	~Arrow();

	void updateSpecificUnitEntity(float _dt);
};