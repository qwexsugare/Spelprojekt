#pragma once

#include "skill.h"
#include "EntityHandler.h"

class DeadlyStrike : public Skill
{
private:
	unsigned int m_senderId;
public:
	static const unsigned int COST = 2000;

	DeadlyStrike();
	~DeadlyStrike();

	bool activate(unsigned int _senderId);
	void updateSpecificSkill(float dt);
};

