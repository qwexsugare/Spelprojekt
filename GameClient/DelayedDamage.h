#pragma once

#include "ServerEntity.h"
#include "EntityHandler.h"
#include "SkillIdHolder.h"

class DelayedDamage : public ServerEntity
{
private:
	float m_timeToImpact;
	unsigned int m_caster;
	unsigned int m_target;

	int m_physicalDamage;
	int m_mentalDamage;
public:
	DelayedDamage(unsigned int _caster, unsigned int _target, float _timeToImpact, int _physicalDamage, int _mentalDamage, Skill::SKILLS skillId, float _animationSpeed);
	~DelayedDamage();

	void update(float dt);
};