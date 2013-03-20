#pragma once

#include "skill.h"
#include "EntityHandler.h"
#include "DelayedDamage.h"
#include "SkillIdHolder.h"

class MeleeAOEAttack :
	public Skill
{
public:
	static const float RANGE;
	static const float AOE_RANGE;
	static const float MINIMUM_DAMAGE_MULTIPLIER;

	MeleeAOEAttack();
	~MeleeAOEAttack();

	virtual bool activate(unsigned int _targetId, unsigned int _senderId);

	void updateSpecificSkill(float dt);
	float getMinimumDamageMultiplier();
};

