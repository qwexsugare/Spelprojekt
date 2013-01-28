#pragma once

#include "skill.h"
#include "EntityHandler.h"

class LifestealingStrike : public Skill
{
private:
	unsigned int m_senderId;
public:
	LifestealingStrike();
	~LifestealingStrike();

	void activate(unsigned int _senderId);
};

