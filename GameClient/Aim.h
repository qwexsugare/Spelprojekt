#pragma once

#include "Skill.h"
#include "EntityHandler.h"

class Aim : public Skill
{
private:
	unsigned int m_senderId;
public:
	static const unsigned int COST = 1100;

	Aim(unsigned int _senderId);
	~Aim();

	void updateSpecificSkill(float dt);
};

