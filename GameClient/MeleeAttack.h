#pragma once

#include "skill.h"
#include "EntityHandler.h"
#include "DelayedDamage.h"
#include "SkillIdHolder.h"

class MeleeAttack : public Skill
{
public:
	static const float RANGE;

	MeleeAttack();
	~MeleeAttack();

	virtual bool activate(unsigned int _targetId, unsigned int _senderId);

	void updateSpecificSkill(float dt);
};