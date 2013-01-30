#pragma once

#include "skill.h"
#include "EntityHandler.h"

class PoisonStrike : public Skill
{
private:
	unsigned int m_senderId;
public:
	static const unsigned int COST = 1700;

	PoisonStrike();
	~PoisonStrike();

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float dt);
};