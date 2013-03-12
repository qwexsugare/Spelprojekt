#pragma once

#include "skill.h"
#include "EntityHandler.h"
#include "DelayedDamage.h"

class PoisonStrike : public Skill
{
private:
	unsigned int m_senderId;
public:
	static const unsigned int COST = 1700;
	static const int POISON_STRIKE_CHANCE = 25;

	PoisonStrike();
	~PoisonStrike();

	bool activate(unsigned int _targetId, unsigned int _senderId);
	void updateSpecificSkill(float dt);
	int getCost();
};