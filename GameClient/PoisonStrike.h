#pragma once

#include "skill.h"
#include "EntityHandler.h"

class PoisonStrike : public Skill
{
private:
	unsigned int m_senderId;
public:
	PoisonStrike();
	~PoisonStrike();

	bool activate(unsigned int _senderId);
};

