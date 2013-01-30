#pragma once

#include "skill.h"
#include "EntityHandler.h"

class LifestealingStrike : public Skill
{
private:
	unsigned int m_senderId;
public:
	static const unsigned int COST = 2200;

	LifestealingStrike();
	~LifestealingStrike();

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float dt);
};

