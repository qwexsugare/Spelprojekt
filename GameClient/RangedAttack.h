#pragma once
#include "skill.h"
#include "EntityHandler.h"
#include "DelayedDamage.h"
#include "SkillIdHolder.h"

class RangedAttack : public Skill
{
public:
	static const float RANGE;
	static const int VELOCITY = 7.0f;

	RangedAttack();
	~RangedAttack();

	virtual bool activate(unsigned int _targetId, unsigned int _senderId);

	void updateSpecificSkill(float dt);
};

